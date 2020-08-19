/* 
 * @description: ScanConnection: Script respons�vel por lidar com a conex�o da p�gina do
 * browser com a aplica��o ScanFromWeb.
 * 
 * @author Lu�s Augusto Weber Mercado [luis_augusto@solis.com.br]
 * @maintainer Lu�s Augusto Weber Mercado [luis_augusto@solis.com.br]
 */

var ScanConnection = {
    isScanning: false, // True quando o scanner est� rodando.
    isConnected: false, // True quando a conex�o com o servidor est� aberta.
    interval: null,
    ws: null,
    currentImg: null,
    
    /* Objeto que possui as prefer�ncias do script. */
    prefs:
    {
        port: 9631, 
        host: 'localhost',
        serviceName: 'scanFromWebWs',
        imgWidth: 265,
        imgHeight: 375,
        disconnectedColor: '#f77',
        connectedColor: '#7f7'
        
    },            
    
    /* Objeto que possui a refer�ncia dos elementos usados. */
    elemns:
    {
        btnScan: null,
        btnConfirmScan: null,
        labelState: null,
        imgContainer: null
        
    },
    
    /* M�todo que instancia com os elementos informados os utilizados na p�gina. */
    initElements: function(btnScan, btnConfirmScan, labelState, imgContainer)
    {
        this.elemns.btnScan = btnScan;
        this.elemns.btnConfirmScan = btnConfirmScan;
        this.elemns.labelState = labelState;
        this.elemns.imgContainer = imgContainer;
        
    },
    
    /* Faz a conex�o com a aplica��o. */
    connect: function()
    {
        if(window.WebSocket)
        {
            var address = 'ws://' + this.prefs.host + ':' + this.prefs.port + '/' + this.prefs.serviceName;
            
            this.ws = new WebSocket(address);
                 
            this.ws.onmessage = function(evt)
            {
                onMessageEvt(evt);
                
            };
            
            /* Esse interval � respons�vel por manter a conex�o com a aplica��o,
             * mudan�a de status etc. */
            this.interval = setInterval(function()
            {
		if(ScanConnection.ws.readyState > 1)
		{
                    ScanConnection.ws = new WebSocket(address);

                    ScanConnection.ws.onmessage = function(evt)
                    {
                        onMessageEvt(evt);

                    };

                    ScanConnection.isConnected = false;

		}
		else if(ScanConnection.ws.readyState === 1)
		{
                    ScanConnection.isConnected = true;
							
		}
		else
		{
                    ScanConnection.isConnected = false;

		}

		if(!ScanConnection.isConnected)
		{
                    setConnectedState(false);
						
		}
		else
		{
                    setConnectedState(true);

		}
                
            }, 2000);
            
        }
        else
        {
            alert('O seu navegador n�o suporta o recurso WebSocket! Esse recurso � necess�rio para o uso da aplica��o. Certifique-se que o mesmo est� na �ltima vers�o ou escolha um mais atualizado.');
            
        }
        
    },
    
    /* M�todo que retorna o base64 pronto para ser utilizado como um atributo
     * 'src' de um <img/> */
    returnImgSrc: function(base64)
    {
        var src = 'data:image/jpeg;base64,' + base64;
        
	return src;
        
    },
    
    /* M�todo que solicita para a aplica��o que escaneie o documento. */
    scan: function()
    {
        if(this.isConnected)
        {
            this.ws.send('scan');

            this.elemns.btnScan.style.visibility = 'hidden';
            ScanConnection.elemns.btnConfirmScan.style.visibility = 'hidden';
            
            this.isScanning = true;
            
            // Mostra a tela de carregamento do SAGU. 
            showLoading();

        }
                    
    },
    
    close: function()
    {
        clearInterval(this.interval);
        this.ws.close();
        setConnectedState(false);
        this.isScanning = false;
        
    }
    
};

/* Evento de mensagem do WebSocket. */
function onMessageEvt(evt)
{
    if(evt.data.substring(0, 4) === 'Data')
    {
        var base64 = evt.data.substring(6);
        
        ScanConnection.currentImg = base64;
        
        ScanConnection.elemns.imgContainer.src = ScanConnection.returnImgSrc(base64);
        ScanConnection.elemns.imgContainer.style.width = ScanConnection.prefs.imgWidth + 'px';
        ScanConnection.elemns.imgContainer.style.height = ScanConnection.prefs.imgHeight + 'px';
        ScanConnection.elemns.zIndex = '0';
        
        ScanConnection.elemns.btnConfirmScan.style.visibility = 'visible';
        ScanConnection.elemns.btnScan.style.visibility = 'visible';
        
        ScanConnection.isScanning = false;
        
    }
    else
    {
        alert('Ocorreu algum erro na hora de escanear o documento! Certifique-se que o aparelho de scanner est� devidamente instalado.');
        
        ScanConnection.elemns.btnScan.style.visibility = 'visible';
        ScanConnection.isScanning = false;
                        
    }
        
    stopShowLoading();
    
}

function setConnectedState(set)
{
    if(set)
    {
        ScanConnection.elemns.labelState.innerHTML = 'Conectado';
        ScanConnection.elemns.labelState.style.background = ScanConnection.prefs.connectedColor;

        ScanConnection.isConnected = true;

        if(!ScanConnection.isScanning)
        {
            ScanConnection.elemns.btnScan.style.visibility = 'visible';

        }
        else
        {
            ScanConnection.elemns.btnScan.style.visibility = 'hidden';
            ScanConnection.elemns.btnConfirmScan.style.visibility = 'hidden';

        }
        
    }
    else
    {
        ScanConnection.elemns.labelState.innerHTML = 'Desconectado';
        ScanConnection.elemns.labelState.style.background = ScanConnection.prefs.disconnectedColor;
        ScanConnection.elemns.btnScan.style.visibility = 'hidden';
        
        ScanConnection.isConnected = true;
        
    }
    
}