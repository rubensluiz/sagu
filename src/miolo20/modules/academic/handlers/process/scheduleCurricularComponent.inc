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
 * Group handler.
 * Contains the menus to access schedule curricular component registers
 *
 * @author Samuel Koch [samuel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Samuel Koch [samuel@solis.coop.br]
 *
 * @since
 * Class created on 16/10/2008
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

if( MIOLO::_request('event') == 'btnSave:click' || $_POST['__EVENTTARGETVALUE'] == 'btnSave:click' )
{
    $MIOLO->checkAccess('FrmGroupAcademic', A_EXECUTE, true, true);
}
else 
{
    $MIOLO->checkAccess('FrmGroupAcademic', A_ACCESS, true, true);
}

$home = 'main:process:scheduleCurricularComponent';
$navbar->addOption(_M('Hor�rio da disciplina oferecida', $module), $module, $home);

$MIOLO->getClass('basic', 'access');
access::insert(_M('Hor�rio da disciplina oferecida', $module), $home, 'group-16x16.png');
$data->home = $home;

$function = MIOLO::_request('function');

$ui = $MIOLO->getUI();

$frmScheduleCurricularComponent = $ui->getForm( $module, 'FrmScheduleCurricularComponent' );
$content                        = $frmScheduleCurricularComponent;

if ( $theme->page->generateMethod != 'generateAJAX' )
{
    $theme->clearContent();
    $theme->insertContent($content);
}

?>
