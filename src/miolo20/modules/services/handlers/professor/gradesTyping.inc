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
 * Pupil grades typing handler.
 * Used to allow the professor to register the pupils grades for the specified group
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Equipe Solis [sagu2@solis.coop.br]
 *
 * @since
 * Class created on 05/09/2007
 */

$module = SAGU::getFileModule(__FILE__);

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('FrmProfessorGradesTyping', A_ACCESS, true, true);

$home = 'main:profmessor:gradesTyping';
$navbar->addOption(_M('Digita��o de notas', $module), $module, $home);

$data->home = $home;

$function = MIOLO::_request('function');
$ui = $MIOLO->getUI();

$frmSectorSearch = $ui->getForm($module,'FrmProfessorGradesTyping', $data);
$frmSectorSearch->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));

$content = $frmSectorSearch;

if ($theme->page->generateMethod != 'generateAJAX')
{
    $theme->clearContent();
    $theme->insertContent($content);
}
?>