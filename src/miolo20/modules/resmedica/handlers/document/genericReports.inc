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
 * Academic generic reports handler.
 * Generates a user-defined report selected by the user.
 *
 * @author Nataniel I. da Silva [nataniel@solis.coop.br]
 *
 * @version $Id$
 *
 * @since
 * Class created on 27/12/2013
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess($module, A_ACCESS, true, true);

$business   = new BusinessBasicBusGenericReports();
$reportData = $business->getReport(MIOLO::_request('reportId'));

$home = 'main:report:genericReports';
$navbar->addOption($reportData->name, $module, $home, null, array('reportId'=>$reportData->reportId));

$data->home = $home;

$ui = $MIOLO->getUI();
$frmGenericReportGen = $ui->getForm('basic','FrmGenericReportGeneration', $data);
$frmGenericReportGen->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
$theme->clearContent();
$theme->insertContent($frmGenericReportGen);

?>

