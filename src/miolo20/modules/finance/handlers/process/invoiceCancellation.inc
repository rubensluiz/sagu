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
 * Invoice cancelation handler.
 * Contains the menus to access process submenus
 *
 * @author Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 *
 * @since
 * Class created on 27/08/2010
 *
 **/

$MIOLO = MIOLO::getInstance();
$module = MIOLO::getCurrentModule();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('FrmInvoiceCancellation', A_EXECUTE, true, true);

$home = 'main:process:invoiceCancellation';
$navbar->addOption(_M('Cancelamento de t�tulos', $module), $module, $home);

$data->home = $home;

$function = MIOLO::_request('function');

$ui = $MIOLO->getUI();
          
$frmPrintInvoice = $ui->getForm( $module, 'FrmInvoiceCancellation', $data );

$content = $frmPrintInvoice;

$theme->clearContent();
$theme->insertContent($content);
?>
