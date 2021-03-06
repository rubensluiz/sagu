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
 * Finance document handler.
 * Contains the menus to access geography submenus
 *
 * @author Eduardo Beal Miglioransa [eduardo@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Eduardo Beal Miglioransa [eduardo@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 16/12/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('finDocument', A_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:document';
$navbar->addOption(_M('Documento', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module,'document/'.$context->shiftAction()) )
{
    $ui       = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module,substr($home,0,strrpos($home,':')));

    $icon        = $ui->getImage($module,'document-16x16.png');
    $pnlDocument = new MActionPanel('pnlDocument', _M('Documento', $module), NULL, $btnClose, $icon);
    $pnlDocument->setIconType('small');
    $pnlDocument->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'),SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem = array(
                      array(_M('Inadimplente',               $module), 'defaulter-16x16.png',               "$home:defaulter"),
                      array(_M('Demonstrativo financeiro',   $module), 'financeDemonstrative-16x16.png',    "$home:financeDemonstrative"),
                      array(_M('Comprovante de pagamento gen�rico', $module), 'paymentVoucherGeneric-16x16.png',   "$home:paymentVoucherGeneric"),
                      array(_M('Desconto na folha de pagamento',        $module), 'payrollDiscountDocument-16x16.png', "$home:payrollDiscount"),
                      array(_M('Boleto interno',        $module), 'internalInvoice-16x16.png',         "$home:internalInvoice"),
                      array(_M('Comprovante fiscal',             $module), 'voucherTax-16x16.png',              "$home:voucherTax"),
                      array(_M('SPC',                     $module), 'spcReport-16x16.png',               "$home:spcReport")
                      );

    $menuItem = SAGU::arraySort($menuItem, 0);
    
    $MIOLO->uses('classes/breport.class','base');
    $breport = new BReport();
    foreach($breport->listReports(BReport::TYPE_DOCUMENT,$module) as $report)
    {
        $menuItem[] = array(_M($report['title'].'*', $module), 'default-16x16.png', "$home:generateReport&report={$report['name']}");
    }
    
    foreach ( $menuItem as $m )
    {
       $pnlDocument->addAction($m[0], $ui->getImage($module,$m[1]), $module, $m[2]);
    }
    $theme->clearContent();
    $theme->insertContent($pnlDocument);
}
?>
