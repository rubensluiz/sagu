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
 * Finance report handler.
 * Contains the menus to access geography submenus
 *
 * @author Armando Taffarel Neto [taffarel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Cristian Edson G�hl [cristian@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Eduardo Beal Miglioransa [eduardo@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 16/12/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('finReport', A_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:report';
$navbar->addOption(_M('Relat�rio', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module,'report/'.$context->shiftAction()) )
{
    $ui       = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module,substr($home,0,strrpos($home,':')));

    $icon        = $ui->getImage($module,'report-16x16.png');
    $pnlReport = new MActionPanel('pnlReport', _M('Relat�rio', $module), NULL, $btnClose, $icon);
    $pnlReport->setIconType('small');
    $pnlReport->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'),SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem = array( 
                       array(_M('Acordos amig�veis', $module), 'folder-16x16.png', "$home:friendlyAgreement"),
                       array(_M('Hist�rico sintetizado', $module), 'summarizedHistory-16x16.png', "$home:summarizedHistory"),
                       array(_M('Hist�rico explanado', $module), 'completeHistory-16x16.png', "$home:completeHistory"),
                       array(_M('Movimenta��es de caixa', $module), 'counterMovementReport-16x16.png', "$home:counterMovementReport"),
                       array(_M('Movimenta��es banc�rias', $module), 'counterMovementReport-16x16.png', "$home:bankMovementReport"),
                       array(_M('Inadimpl�ncia anal�tico', $module), 'defaulterReport-16x16.png', "$home:defaulterReport"),
                       array(_M('Inadimpl�ncia sint�tico', $module), 'defaulterReportSummary-16x16.png', "$home:defaulterReportSummary"),
                       array(_M('Contas a receber detalhado', $module), 'receivableInvoiceReport-16x16.png', "$home:receivableInvoiceReport"),
                       array(_M('Contas a receber resumido', $module), 'receivableInvoiceReport-16x16.png', "$home:receivableInvoiceReportSummary"),
                       array(_M('Relat�rio geral de caixa', $module), 'generalCounterMovement-16x16.png', "$home:generalCounterMovement"),
                       array(_M('Descontos incentivos e financiamentos', $module), 'receivableInvoiceReport-16x16.png', "$home:discountsIncentivesAndLoan")
                     );
                     
    $menuItem = array_merge( SAGU::getGenericReportsMenu($module), $menuItem );

    $menuItem = SAGU::arraySort($menuItem, 0);
    
    $MIOLO->uses('classes/breport.class','base');
    $breport = new BReport();
    foreach($breport->listReports(BReport::TYPE_REPORT,$module) as $report)
    {
        $menuItem[] = array(_M($report['title'].'*', $module), 'default-16x16.png', "$home:generateReport&report={$report['name']}");
    }
    
    foreach ( $menuItem as $m )
    {
       $pnlReport->addAction($m[0], $ui->getImage($module,$m[1]), $module, $m[2], $m[3], $m[4]);
    }
    $theme->clearContent();
    $theme->insertContent($pnlReport);
}

?>
