<?php
/**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Solu��es Livres Ltda.
 *
 * Este arquivo � parte do programa Sagu.
 *
 * O Sagu � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
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
 * Sagu2 main handler.
 * Contains the basic menus to access submenus
 *
 * @author Daniel Afonso Heisler [daniel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 09/08/2006
 */

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

if ( !$module )
{
    $module = 'sagu2';
}

if ( ($sa = $context->shiftAction()) != NULL )
{
    $a = $sa;
}
elseif ( $module != 'sagu2' )
{
    $a = 'main';
}

if ( SAGU::isUserLogged() )
{
    $ui = $MIOLO->getUI();

    $theme->clearContent();
    
    $handled = $MIOLO->invokeHandler($module,$a);
    
    //Verifica se existe uma configura��o para troca de senha e redireciona para tela de troca
    if( BusinessBasicBusConfiguracaoTrocaDeSenha::verificaTrocaDeSenha() == DB_TRUE )
    {
        $content =  $ui->getForm('sagu2', 'FrmTrocaDeSenha');
        $theme->setContent($content);
    }
    
    //MIOLO2 menu
    include_once($MIOLO->getConf('home.modules') .'/sagu2/handlers/menu.inc');
    
    if ( $MIOLO->getConf('options.widgets') == 'true' )
    {
        $content =  $ui->getForm($module, 'FrmPrincipal');
        $theme->setContent($content);
    }
    else
    {
    }
}
else
{
    $ui = $MIOLO->getUI();
    $content =  $ui->getForm('admin', $MIOLO->getConf('options.authmd5') ? 'frmLoginMD5' : 'frmLogin');
    $theme->setContent($content);
}
?>
