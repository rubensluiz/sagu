<?php

/**
 * <--- Copyright 2011-2015 de Solis - Cooperativa de Solu��es Livres Ltda.
 *
 * Este arquivo � parte do programa Base.
 *
 * O Fermilab � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * dentro dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o
 * do Software Livre (FSF); na vers�o 2 da Licen�a.
 *
 * Este programa � distribu�do na esperan�a que possa ser �til, mas SEM
 * NENHUMA GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO
 * ou APLICA��O EM PARTICULAR. Veja a Licen�a P�blica Geral GNU/GPL em
 * portugu�s para maiores detalhes.
 *
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU, sob o t�tulo
 * "LICENCA.txt", junto com este programa, se n�o, acesse o Portal do Software
 * P�blico Brasileiro no endere�o www.softwarepublico.gov.br ou escreva para a
 * Funda��o do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 *
 * Manipulador de formul�rios. Adapta��o da vers�o do MIOLO26 para o MIOLO20
 *
 * @author Daniel Hartmann [daniel@solis.coop.br]
 * @author Jader Osvino Fiegenbaum [jader@solis.coop.br]
 * @author Lu�s Augusto Weber Mercado [luis_augusto@solis.com.br]
 *
 * @since
 * Arquivo criado em 03/06/2015
 */
$MIOLO = MIOLO::getInstance();
$MIOLO->uses("classes/bBaseDeDados.class.php", "base");
$MIOLO->uses("classes/bCatalogo.class.php", "base");
$MIOLO->uses("classes/bInfoColuna.class.php", "base");

$modulo = MIOLO::getCurrentModule();

$acao = MIOLO::getCurrentAction();

// Obt�m a type da a��o
$type = MIOLO::_REQUEST('type');

global $navbar;
$navbar->addOption(_M(AdmMioloTransaction::obterNomeDaTransacao("Frm" . $type), $modulo), $modulo, $acao);

// Faz a manipula��o de formul�rios caso exista uma type
if ( $type )
{
    limpaConteudoTema();
    
    try
    {
        bManipular($type);
    }
    catch( Exception $e )
    {
        SAGU::error($e->getMessage(), $MIOLO->GetActionURL("sagu2", "main"));

    }
}

// Chama handler do lookup, logout ou login
if ( in_array($acao, array('lookup', 'logout', 'login') ) )
{
    $MIOLO->invokeHandler($modulo, $acao);
}

/**
 * Fun��o para manipular formul�rios
 * 
 * @param String $type Tipo manipulado pelo formul�rio
 */
function bManipular($type)
{
    $nomeFormulario = 'Frm' . $type;
    $temAcessoAoFormulario = verificaAcessoFormulario($nomeFormulario);
    
    if ($temAcessoAoFormulario)
    {
        renderizarFormulario($type);
    }
}

/**
 * Limpa o conte�do atual do tema
 * 
 */
function limpaConteudoTema()
{
    $theme = MIOLO::getInstance()->getTheme();
    $theme->clearContent();
}

/**
 * Obt�m e renderiza o formul�rio
 * 
 * @param String $type Nome do tipo manipulado pelo formul�rio
 */
function renderizarFormulario($type)
{
    list($formulario, $modulo) = obterFormularioPelaFuncaoETipo(MIOLO::_REQUEST("function"), $type);

    $MIOLO = MIOLO::getInstance();
    
    $conteudo = $MIOLO->getUI()->getForm($modulo, $formulario, obterParametrosParaFormularioPeloTipo($type));

    $MIOLO->getTheme()->setContent($conteudo);
}

/**
 * Obt�m as informa��es do formul�rio de pesquisa e de edi��o para o type
 * 
 * @param String $funcao Fun��o requisitada
 * @param String $type Nome do tipo manipulado
 * @return Array Lista com o formul�rio e o m�dulo deste
 */
function obterFormularioPelaFuncaoETipo($funcao, $type)
{
    $modulo = MIOLO::getCurrentModule();
    $informacaoFormulario = null;
    
    switch ($funcao)
    {
        case SForm::FUNCTION_INSERT:
        case SForm::FUNCTION_UPDATE:
        case SForm::FUNCTION_DELETE:
            $informacaoFormulario = obterFormularioDeEdicao($modulo, $type);
                        
            break;

        case SForm::FUNCTION_SEARCH:
        default:
            $informacaoFormulario = obterFormularioDePesquisa($modulo, $type);
    }
    
    return $informacaoFormulario;
}

/**
 * Obt�m o formul�rio de edi��o para o tipo especificado
 * 
 * @param String $modulo Nome do m�dulo original
 * @param String $type Nome do type manipulado
 * @return Array Lista com o formul�rio e o m�dulo deste. Caso o formul�rio respectivo
 * do tipo n�o tenha sido encontrado, retorna a refer�ncia ao formul�rio "FrmDinamico"
 */
function obterFormularioDeEdicao($modulo, $type)
{
    $formularioCadastro = obterNomeFormularioParaGeracao($modulo, $type);

    // Verifica se o c�digo do formul�rio existe
    if ( !$formularioCadastro )
    {
        $formularioCadastro = 'FrmDinamico';
        $modulo = 'basic';
    }
    
    return array($formularioCadastro, $modulo);
    
}

/**
 * Obt�m o formul�rio de pesquisa para o tipo especificado
 * 
 * @param String $modulo Nome do m�dulo original
 * @param String $type Nome do type manipulado
 * @return Array Lista com o formul�rio e o m�dulo deste. Caso o formul�rio respectivo
 * do tipo n�o tenha sido encontrado, retorna a refer�ncia ao formul�rio "FrmDinamicoSearch"
 */
function obterFormularioDePesquisa($modulo, $type)
{
    $formularioBusca = obterNomeFormularioParaGeracao($modulo, $type . 'Search');

    // Verifica se o c�digo do formul�rio existe
    if ( !$formularioBusca )
    {
        $formularioBusca = 'FrmDinamicoSearch';
        $modulo = 'basic';
    }
    
    return array($formularioBusca, $modulo);
}

/**
 * Obt�m os par�metros para o formul�rio
 * 
 * @param String $type Tipo manipulado pelo formul�rio
 * @return Array Lista com os par�metros
 */
function obterParametrosParaFormularioPeloTipo($type)
{
    $modulo = MIOLO::getCurrentModule();
    $funcao = MIOLO::_REQUEST('function');
        
    return array(
        'modulo' => $modulo,
        'funcao' => $funcao,
        'tipo' => $type
    );
    
}

/**
 * Obt�m o nome do formul�rio para gera��o din�mica
 * 
 * @param String $modulo Modulo do formul�rio
 * @param String $nome Nome do tipo a ter seu formul�rio procurado
 * @return String|Boolean Nome do fomul�rio a ser gerado, FALSE caso este n�o seja
 * econtrado
 */
function obterNomeFormularioParaGeracao($modulo, $nome)
{
    $MIOLO = MIOLO::getInstance();

    $nomeFormulario = 'Frm' . $nome;
    $caminhoFormulario = $MIOLO->getModulePath($modulo, 'forms/' . $nomeFormulario . '.class');
    
    if ( file_exists($caminhoFormulario) )
    {
        return $nomeFormulario;
    }
    
    return false;
}

/**
 * Veririfica o acessso ao formul�rio
 * 
 * @param String $nomeFormulario Nome da transa��o do formul�rio
 * @return Boolean Se � poss�vel ou n�o o usu�rio atual entrar no formul�rio
 */
function verificaAcessoFormulario($nomeFormulario)
{
    $MIOLO = MIOLO::getInstance();
    $funcao = MIOLO::_REQUEST('function');
    
    $permissao = obterPermissaoPelaFuncao($funcao);
    
    return $MIOLO->checkAccess($nomeFormulario, $permissao, true, true);
    
}

/**
 * Obt�m a permiss�o necess�ria conforme a fun��o desejada
 * 
 * @param String $funcao Fun��o do formul�rio
 * @return Inteiro Valor da constante representando a fun��o
 */
function obterPermissaoPelaFuncao($funcao)
{
    $perms = array(
        SForm::FUNCTION_INSERT => A_INSERT,
        SForm::FUNCTION_UPDATE => A_UPDATE,
        SForm::FUNCTION_DELETE => A_DELETE,
        SForm::FUNCTION_SEARCH => A_ACCESS,
        "" => A_ACCESS
    );
    
    return $perms[$funcao];
    
}
?>