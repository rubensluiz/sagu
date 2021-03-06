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
 * Finacne process handler.
 * Contains the menus to access process submenus
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 07/12/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess($module, A_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:process:remittanceReturn:remittanceInvoice';

if ( !$MIOLO->invokeHandler($module,'process/remittanceReturn/'.$context->shiftAction()) )
{
    $ui       = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':')));

    $icon       = $ui->getImage($module, 'process-16x16.png');
    $pnlInvoice = new MActionPanel('pnlInvoice', _M('Remessa de t�tulos', $module), null, $btnClose, $icon);
    $pnlInvoice->setIconType('small');
    $pnlInvoice->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'), SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));
    $businessBanks = new BusinessFinanceBusBank();
    $banks = $businessBanks->listBank();

    // If exists banks registered search the classes available for that
    if (is_array($banks[0]))
    {
        $MIOLO->getClass($module, 'RemittanceInvoice');
        $invoiceRemittance = new remittanceInvoice();
        foreach ($banks as $b)
        {
            if ($invoiceRemittance->remittanceExists($b[0]))
            {
                $items = array($b[1], 'remittanceInvoice'.$b[0].'-16x16.png', "$home:remittanceInvoice".$b[0]);
                $menuItem[] = $items;
            }
            unset($items);
        }
    }
    
    $sortMenuItem = SAGU::arraySort($menuItem, 0);

    foreach ( $sortMenuItem as $m )
    {
        $pnlInvoice->addAction($m[0], $ui->getImage($module, $m[1]), $module, $m[2]);
    }

    $menu = array($pnlInvoice);
    $theme->clearContent();
    $theme->insertContent($menu);
}
?>
