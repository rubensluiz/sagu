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
 * Academic scholarship description technician  handler.
 * Contains the menus to access center registers
 *
 * @author Andre Chagas Dias [andre@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 03/12/2008
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('FrmScholarshipDescriptionTechnician', A_EXECUTE, true, true);

$home = 'main:document:scholarshipDescriptionTechnician';
$navbar->addOption(_M('Hist�rico t�cnico', $module), $module, $home);

$MIOLO->getClass('basic', 'access');
access::insert(_M('Hist�rico t�cnico', $module), $home, 'scholarshipDescriptionTechnician-16x16.png');
$data->home = $home;

$function = MIOLO::_request('function');

$ui = $MIOLO->getUI();

$frmScholarshipDescriptionTechnician = $ui->getForm($module,'FrmScholarshipDescriptionTechnician', $data);
$frmScholarshipDescriptionTechnician->setClose($MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':'))));
$content = $frmScholarshipDescriptionTechnician;

$theme->clearContent();
$theme->insertContent($content);

?>