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
 * Finance main handler.
 * Contains the basic menus to access submenus
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
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
 * Class created on 17/08/2005
 */

$MIOLO->trace( 'file:' . $_SERVER['SCRIPT_NAME'] );
$module = MIOLO::getCurrentModule();

$function = MIOLO::_request( 'function' );
if ($function == 'resetStack')
{
    SAGU::resetStack();
}

$home = 'main';
$navbar->addOption( _M('Financeiro', $module ), $module, $home, null, array( 'function' => 'resetStack' ) );

//MIOLO2 menu
include_once ($MIOLO->GetConf( 'home.modules' ) . '/sagu2/handlers/menu.inc');

// Inclui o manipulador
$type = MIOLO::_REQUEST("type", "GET");

if ( strlen($type) > 0 )
{
    $MIOLO->uses('handlers/manipulador.inc.php', 'base');
}
else
{
    $ui = $MIOLO->getUI();

    if ( !$MIOLO->invokeHandler($module, $context->shiftAction()))
    {
        $MIOLO->checkAccess('FINANCE', A_ACCESS, true, true);

        /* Diverse consultation */
        $a = new Separator( );
        $frmDiverseConsultation = $ui->getForm( $module, 'FrmDiverseConsultation', $data );
        $frmDiverseConsultation->setClose( $btnClose );

        if ( $theme->page->generateMethod != 'generateAJAX' )
        {
            $theme->clearContent();
            $theme->AppendContent($frmDiverseConsultation);
        }
    }
}
?>
