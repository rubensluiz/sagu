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
 * Control copies register handler.
 * Contains the menus to access register submenus
 *
 * @author Jamiel Spezia [jamiel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Rafael Lu�s Spengler [rafael@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 17/08/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess($module, CCP_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:register';
$navbar->addOption(_M('Cadastro', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module,'register/'.$context->shiftAction()) )
{

    $ui       = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module,substr($home,0,strrpos($home,':')));

    $icon                = $ui->getImage($module,'register-16x16.png');
    $pnlControlCopies = new MActionPanel('pnlControlCopies', _M('Cadastro', $module), null, $btnClose, $icon);
    $pnlControlCopies->setIconType('small');
    $pnlControlCopies->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'),SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem = array(
                       array(_M('C�pias', $module),        'copy-16x16.png',    "$home:copy"),
                       array(_M('Setor', $module),        'copy-16x16.png',    "$home:sector"),
                       array(_M('Per�odo', $module),        'copy-16x16.png',    "$home:period")
                        );

    if ( SAGU::getParameter('BASIC', 'MODULE_ACADEMIC_INSTALLED') == 'YES' )
    {
        $menuItem[] = array(_M('Projeto',$module),           'project-16x16.png', "$home:project");
        $menuItem[] = array(_M('Requisi��o',$module),        'request-16x16.png', "$home:request");
        $menuItem[] = array(_M('Regras',  $module),          'rule-16x16.png',    "$home:rule");
        $menuItem[] = array(_M('Servi�o',$module),           'service-16x16.png', "$home:service");
        $menuItem[] = array(_M('Desconto em folha',$module), 'payrolldiscount-16x16.png', "$home:payrolldiscount");
    }

    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    foreach ( $sortMenuItem as $m )
    {
       $pnlControlCopies->addAction($m[0], $ui->getImage($module,$m[1]), $module, $m[2],
       $module, $m[3], $module, $m[4], $module, $m[5], $module, $m[6]);
    }

    $theme->clearContent();
    $theme->insertContent($pnlControlCopies);

}

?>
