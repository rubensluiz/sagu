/**
 * Solis, Cooperativa de Solu��es Livres
 * Script que cria a visualiza��o da matriz curricular para o Sagu
 *
 * Autor: Lu�s Augusto Weber Mercado [luis_augusto@solis.com.br]
 *
 * Observa��o: Script focado no miolo 20.
 */

var VisualizacaoMatriz = {
    
    /**
     * Var�aveis "globais"
     * 
     */
    Vars: {
        dados: [],
        numeroSemestres: 0,
        grupos: [],
        totalDepsNumber: 0,
        drawnLines: 0
                
    },
    
    /**
     * Objeto que cont�m as prefer�ncias. Estas podem ser modificadas diretamente.
     * 
     */
    Preferencias: {
        disciplinDefaultColor: "#1F72BF",
        disciplinElementMinHeight: 34,
        disciplinElementInitMargin: 55,
        types: null,
        groupColors: null

    },
    
    /**
     * Objeto que cont�m as refer�ncias dos elementos. � inicializado pelo m�todo 'initElements'.
     * 
     */
    Elementos: {
        parent: null,
        table: null,
        canvas: null,
        divLegenda: null

    },
    
    /**
     * M�todo que inicializa o objeto de Elementos para futuras refer�ncias.
     * 
     * @param {DOMElement, Div} parent Div que cont�m os elementos. 
     * @param {DOMElement, Table} table Tabela onde s�o adicionadas as disciplinas.
     * @param {DOMElement, Canvas} canvas Canvas (�rea) onde s�o desenhadas as rela��es.
     */
    initElements: function(parent, table, canvas)
    {
        this.Elementos.parent = parent;
        this.Elementos.table = table;
        this.Elementos.canvas = canvas;
        
        var div = document.createElement('div'),
            p = document.createElement('p');
    
        p.className = 'legenda-matriz-title';
        p.innerHTML = "Legenda &#8657";
                
        div.id = 'divMatrizLegenda';
        div.className = 'legenda-matriz closed';
        
        div.addEventListener('click', function()
        {
            var classes = this.className.split(/\s+/),
                p = document.querySelector('p.legenda-matriz-title'),
                elem = this.childNodes,
                display = 'inline-table';
            
            if(classes[1] === 'closed')
            {
                this.className = 'legenda-matriz opened';
                p.innerHTML = VisualizacaoMatriz.util_convertHtmlToText('Legenda &#8659');
                                
            }
            else if(classes[1] === 'opened')
            {
                this.className = 'legenda-matriz closed';
                p.innerHTML = VisualizacaoMatriz.util_convertHtmlToText('Legenda &#8657');
                
                display = 'none';
                
            }
            
            for(var i = 0; i < elem.length; i++)
            {
                if(elem[i].className !== 'legenda-matriz-title')
                {
                    elem[i].style.display = display;
                    
                }
                                
            }
                        
        }, false);
        
        div.appendChild(p);
        
        this.Elementos.divLegenda = div;
                
    },
    
    /**
     * M�todo 'main' do script. � respons�vel por montar a estrutura chamando todos os outros m�todos.
     * 
     * @param {Array} dados Dados das disciplinas, informa��es dos semestres etc.
     * @param {DOMElement, Div} parent Div que cont�m os elementos. 
     * @param {DOMElement, Table} table Tabela onde s�o adicionadas as disciplinas.
     * @param {DOMElement, Canvas} canvas Canvas (�rea) onde s�o desenhadas as rela��es.
     * @param {boolean} dividir true para dividir as disciplinas por grupo e separ�-las em se��o.
     */
    montaEstrutura: function(dados, parentDiv, disciplinTable, relationCanvas, dividir)
    {
        /* Setup inicial */
        
        this.Vars.dados = dados;
        
        // Inicializa os elementos.
        this.initElements(parentDiv, disciplinTable, relationCanvas);
                
        // Cria um table row.
        this.Elementos.table.appendChild(document.createElement('tr'));
        
        // O n�mero de semestres � igual ao n�mero de itens no array 'dados'.
        this.Vars.numeroSemestres = dados.length;
        
        // Faz a navega��o inicial para criar as colunas e distribuir as disciplinas entre os grupos.
        for(var i = 0; i < dados.length; i++)
        {
            this.util_criaColuna(dados[i].desc);
            
            for(var j = 0; j < dados[i].disciplinas.length; j++)
            {
                var adicionar = true,
                    disciplina = dados[i].disciplinas[j],
                    grupo = disciplina.grupo;
                                
                for(var k = 0; k < this.Vars.grupos.length; k++)
                {
                    if(this.Vars.grupos[k][0].id === grupo.id)
                    {
                        adicionar = false;
                        
                        this.Vars.grupos[k][1][this.Vars.grupos[k][1].length] = [disciplina, i];
                        
                    }
                                        
                }
                
                if(adicionar)
                {
                    this.Vars.grupos[this.Vars.grupos.length] = [grupo, [[disciplina, i]]];
                                                          
                }
                
            }
            
        }
        
        // Ap�s a cria��o da estrutra base, chama-se o m�todo que preenche a tabela com os dados.
        this.util_criaDisciplinas(dividir);
                
        /* Ajustes nos elementos*/
        
        var ajustSize = [this.Elementos.table.scrollWidth, this.Elementos.table.scrollHeight];
                
        // Ajusta o canvas.
        this.Elementos.canvas.width = ajustSize[0];
        this.Elementos.canvas.height = ajustSize[1];
        
        this.Elementos.parent.style.width = ajustSize[0] + 'px';
        this.Elementos.parent.style.height = ajustSize[1] + 'px';
        
        // Ajusta o popup para ficar do tamanho dispon�vel da janela.
        var validatePopupInterval = setInterval(function()
        {
            // BASIC, MIOLO 20
            var popup = document.getElementById('mPopup');
            
            // Se o popup n�o for null, realiza os ajustes.
            if( popup !== null )
            {
                popup.style.right = '0px';
                popup.style.maxHeight = '100%';
                popup.style.top = '0px';
                popup.style.bottom = '0px';
                popup.style.left = '0px';
                
                // Seta a posi��o do t�tulo do popup como fixed.
                document.getElementById('popupTitle').style.position = 'fixed';
                //document.getElementById('popupTitle').style.position = 'fixed';

                // Adiciona um listener para eventos de scroll, para fazer com que o cabe�alho acompanhe a rolagem.
                document.getElementById('mPopup').addEventListener('scroll', function()
                {
                    var header = VisualizacaoMatriz.Elementos.table.firstChild,
                        scrollTop = this.scrollTop,
                        nodes = null;
                        
                    nodes = header.childNodes;

                    for(var i = 0; i < nodes.length; i++)
                    {
                        nodes[i].firstChild.style.top = (scrollTop - 9) + 'px';
                        
                    }

                }, false);

                clearInterval(validatePopupInterval);

            }
            
            // PORTAL, MIOLO 26
            // Ajusta o popup para ficar do tamanho dispon�vel da janela.
            /*var popup = document.querySelector('div.dijitDialog');
            
            // Se o popup n�o for null, realiza os ajustes.
            if( popup !== null )
            {
                popup.style.right = '0px';
                popup.style.maxHeight = '100%';
                popup.style.top = '0px';
                popup.style.bottom = '0px';
                popup.style.left = '0px';

                // Seta a posi��o do t�tulo do popup como fixed.
                document.querySelector('span.dijitDialogTitle').style.position = 'fixed';
                //document.getElementById('popupTitle').style.position = 'fixed';

                // Adiciona um listener para eventos de scroll, para fazer com que o cabe�alho acompanhe a rolagem.
                popup.addEventListener('scroll', function()
                {
                    var header = VisualizacaoMatriz.Elementos.table.firstChild,
                        scrollTop = this.scrollTop,
                        nodes = null;
                        
                    nodes = header.childNodes;

                    for(var i = 0; i < nodes.length; i++)
                    {
                        nodes[i].firstChild.style.top = (scrollTop - 9) + 'px';
                        
                    }

                }, false);

                clearInterval(validatePopupInterval);

            }*/

        }, 10);
        
        this.util_doRelations(dados);
        
        this.Elementos.parent.appendChild(this.Elementos.divLegenda);
                
    },
    
    /**
     * Cria o header da tabela.
     * 
     * @param {String} title T�tulo do semestre.
     */
    util_criaColuna: function(title)
    {
        var th = document.createElement('th'),
            p = document.createElement('p'),
            header = this.Elementos.table.firstChild;
            
        p.innerHTML = title;
        p.className = 'semester-title';
        
        th.appendChild(p);
        
        header.appendChild(th);
        
    },
    
    /**
     * Navega entre os grupos e adiciona os elementos a tabela.
     * 
     * @param {boolean} dividir Se true, divide as disciplinas por grupos em diferentes rows.
     */
    util_criaDisciplinas: function(dividir)
    {
        var tr = document.createElement('tr');
                
        // Cria os <td>'s conforme o n�mero de semestres.
        for(var j = 0; j < this.Vars.numeroSemestres; j++)
        {
            var td = document.createElement('td');

            td.id = 'semestre-' + j;
            
            td.className = 'vAlignTop';
            
            tr.appendChild(td);

        }
        
        // Navega pelos grupos
        for(var i = 0; i < this.Vars.grupos.length; i++)
        {
            var grupo = this.Vars.grupos[i];
                        
            if(dividir)
            {
                var tr = document.createElement('tr');
                
                tr.id = 'grupo-' + grupo[0].id;
                
                // Cria os <td>'s conforme o n�mero de semestres.
                for(var j = 0; j < this.Vars.numeroSemestres; j++)
                {
                    var td = document.createElement('td');

                    td.id = 'g' + grupo[0].id + 'semestre-' + j;

                    td.className = 'vAlignMiddle';

                    tr.appendChild(td);

                }
                
            }
             
            // Adiciona o novo row a tabela.
            this.Elementos.table.appendChild(tr);

            // Pega todos os <td>'s para adicionar as respectivas disciplinas.
            var nodes = tr.childNodes,
                color = null;

            if(this.Preferencias.groupColors !== null)
            {
                color = this.Preferencias.groupColors.getColor(grupo[0].id);

            }
            else
            {
                // Gera cor baseada no n�mero total de itens.
                color = this.util_rainbow(this.Vars.grupos.length, i, true);

            }
            
            // Adiciona o grupo com sua descri��o a legenda
            this.util_addLegendItem(grupo[0].nome, color);
            
            // Navega entre os itens por grupo.
            for(var k = 0; k < grupo[1].length; k++)
            {
                var info = grupo[1][k];

                // O que criar, onde criar e a cor
                this.util_criaElementoDisciplina(info[0], nodes[info[1]], color);

                // Soma as depend�ncias. Esse valor � essencial na cria��o das rela��es.
                this.Vars.totalDepsNumber+= info[0].deps.length;
                // Corre��o de margem se for o primeiro grupo, sem a corre��o o cabe�alho fica acima.
                
            }
            
            if(i === 0)
            {
                tr.style.marginTop = '40px';

            }
                                     
        }
                
    },
    
    /**
     * Cria o elemento de disciplina no semestre e na row informados.
     * 
     * @param {Object} disciplina Objeto com as inform��es da disciplina.
     * @param {DOMElement, Td} semestre Elemento td em que se deve adicionar a disciplina.
     * @param {String} color Cor no formato hexadecimal (#rrggbb).
     */
    util_criaElementoDisciplina: function(disciplina, semestre, color)
    {
        var div = document.createElement('div'),
            p = document.createElement('p'),
            compl = '</span>',
            compl2 = '',
            border = this.util_getTypeColor(disciplina.tipo.id),
            text = '',
            tempo = 0;
        
        if(disciplina.nome.length > 20)
        {
            compl = '...' + compl;
            
        }
        
        text = "Nome: " + disciplina.nome + '&#13;'
             + "Tipo: " + disciplina.tipo.desc + '&#13;'
             + "Horas: " + disciplina.tempo + "h" + "&#13;"
             + "Grupo: " + disciplina.grupo.nome + "&#13;";
     
        // Pega as outras op��es e anexa ao hint.
        if(disciplina.info !== null)
        {
            text = this.util_addOtherInfo(text, disciplina.info);
            
        }
                
        div.className = 'disciplin';
        div.title = this.util_convertHtmlToText(text);
        div.style.backgroundColor = color;
        div.style.border = border === null ? '' : '2px solid ' + border;
        div.id = 'disciplina' + disciplina.id;
        
        tempo = Math.floor(parseInt(disciplina.tempo) / 1.5);
        
        if(tempo > this.Preferencias.disciplinElementMinHeight)
        {
            // Div de height proporcional a carga hor�ria.
            div.style.height =  tempo + 'px';
            
        }
        else
        {
            div.style.height =  this.Preferencias.disciplinElementMinHeight + 'px';
            compl2 = 'font-size: 10px;';
            
        }
        
        p.innerHTML = disciplina.id + '<br/><span style="font-weight: normal; ' + compl2 + '">' + disciplina.nome.substr(0, 20) + compl;
        p.className = 'disciplin-text';
                        
        div.appendChild(p);
                
        semestre.appendChild(div);
        
    },
    
    /**
     * Converte o valor informado em 'html' para o correspondente em texto.
     * Utilizado para lidar com as entidades em 'html'.
     * 
     * @param {String} Texto a ser formatado.
     * @returns {String} Cont�m o texto formatado para ser interpretado como texto puro. 
     * 
     */
    util_convertHtmlToText: function(value) {
        var d = document.createElement('div');
        d.innerHTML = value;
        return d.textContent;
        
    },
    
    /**
     * Faz as rela��es de interdepend�ncias entre as disciplinas.
     * 
     * @param {Array} semestres Array com as informa��es dos semestres (disciplinas etc.).
     */
    util_doRelations: function(semestres)
    {
        for(var i = 0; i < semestres.length; i++)
        {
            for(var j = 0; j < semestres[i].disciplinas.length; j++)
            {
                var disciplina = semestres[i].disciplinas[j];
                
                for(var z = 0; z < disciplina.deps.length; z++)
                {
                    // Desenha a rela��o.
                    this.util_drawRelation(document.getElementById('disciplina' + disciplina.id), document.getElementById('disciplina' + disciplina.deps[z]));
                                        
                }
                                
            }
            
        }
        
    },
    
    /**
     * Desenha a rela��o entre as disciplinas no canvas.
     * 
     * @param {DOMElement, Div} who Elemento que tem rela��o.
     * @param {DOMElement, Div} withWho Esta com quem.
     */
    util_drawRelation: function(who, withWho)
    {
        var parentRect = this.Elementos.table.getBoundingClientRect(),
            whoRect = who.getBoundingClientRect(),
            withWhoRect = withWho.getBoundingClientRect(),
            offsetWho = { left: whoRect.left - parentRect.left, top: whoRect.top - parentRect.top },
            offsetWithWho = { left: withWhoRect.left - parentRect.left, top: withWhoRect.top - parentRect.top },
            context = this.Elementos.canvas.getContext("2d"),
            color = this.util_rainbow(this.Vars.totalDepsNumber, this.Vars.drawnLines),
            startPoint = [],
            endPoint = [];
            
        // Cria os pontos de refer�ncia.
        startPoint = [offsetWithWho.left + whoRect.width, Math.round(offsetWithWho.top + (withWhoRect.height / 2))];
        endPoint = [offsetWho.left, Math.round(offsetWho.top + (whoRect.height / 2))];
                        
        context.strokeStyle = color;
        
        // 0 ==> x; 1 ==> y
        context.beginPath();
        context.moveTo(startPoint[0] - 1, startPoint[1]);
        context.lineTo(endPoint[0], endPoint[1]);
        context.lineWidth = 3;
        context.stroke();
        
        // Desenha um c�rculo no final da linha.
        context.beginPath();
        context.arc(endPoint[0], endPoint[1], 10, 0, 2 * Math.PI, false);
        context.fillStyle = color;
        context.fill();
        
        this.Vars.drawnLines++;
        
    },
    
    /**
     * M�todo que retorna uma cor que � relativa ao n�mero de elementos.
     * 
     * @param {Integer} numOfSteps N�mero total.
     * @param {Integer} step N�mero relativo ao total.
     * @param {boolean} darker Se a cor deve ser mais escura.
     * @returns {String} Cor no formato hexadecimal (#rrggbb).
     */
    util_rainbow: function(numOfSteps, step, darker)
    {
        // This function generates vibrant, "evenly spaced" colours (i.e. no clustering). This is ideal for creating easily distinguishable vibrant markers in Google Maps and other apps.
        // Adam Cole, 2011-Sept-14
        // HSV to RBG adapted from: http://mjijackson.com/2008/02/rgb-to-hsl-and-rgb-to-hsv-color-model-conversion-algorithms-in-javascript
        var r, g, b;
        var h = step / numOfSteps;
        var i = ~~(h * 6);
        var f = h * 6 - i;
        var q = 1 - f;
        var coe = 255;
        
        if(darker)
        {
            coe = 200;
            
        }
        
        switch(i % 6){
            case 0: r = 1, g = f, b = 0; break;
            case 1: r = q, g = 1, b = 0; break;
            case 2: r = 0, g = 1, b = f; break;
            case 3: r = 0, g = q, b = 1; break;
            case 4: r = f, g = 0, b = 1; break;
            case 5: r = 1, g = 0, b = q; break;
        }
        
        var c = "#" + ("00" + (~ ~(r * coe)).toString(16)).slice(-2) + ("00" + (~ ~(g * coe)).toString(16)).slice(-2) + ("00" + (~ ~(b * coe)).toString(16)).slice(-2);
        return (c);
        
    },
    
    /**
     * 
     * @param {String} tipo contendo um c�digo em forma de string
     * @returns {String} String de cor no formato hexadecimal (#rrggbb).
     */
    util_getTypeColor: function(tipo)
    {
        if(this.Preferencias.types !== null)
        {
            return this.Preferencias.types[tipo];
            
        }
        else
        {
            return null;
            
        }
        
        
    },
    
    /**
     * Adiciona ao texto informado as informa��es desejadas.
     * 
     * @param {String} text Texto a ser adiconada as informa��es.
     * @param {Array} info Array com as informa��es.
     * @returns {String} Texto com as informa��es adicionadas.
     */
    util_addOtherInfo: function(text, info)
    {
        for(var i = 0; i < info.length; i++)
        {
            text += info[i].label + ": " + info[i].desc + "&#13;";
            
        }
        
        return text;
        
    },
    
    util_addLegendItem: function(desc, color)
    {
        var div = document.createElement('div'),
            span = document.createElement('span'),
            wrap = document.createElement('div');
            
        span.innerHTML = desc;
        span.className = 'legenda-item-text';
    
        div.className = 'legenda-item-color';
        div.style.backgroundColor = color;
    
        wrap.appendChild(div);
        wrap.appendChild(span);
        
        wrap.className = 'legenda-item';
        
        this.Elementos.divLegenda.appendChild(wrap);
        
    }
    
};