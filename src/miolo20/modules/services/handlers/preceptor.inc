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
 * Pupil services handler.
 * Used to access the training services
 *
 * @author Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @since
 * Class created on 13/04/2011
 */

$home = 'main:preceptor';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�os do preceptor', $module), $module, $home, null, array('function' => 'resetStack'));

if ( !$MIOLO->invokeHandler($module, 'preceptor/' . $context->shiftAction()) )
{
    $btnClose = $MIOLO->getActionURL('sagu2', 'main');
    $mioloUserName = trim($MIOLO->getLogin()->id);
    
    $pnlPupil = new MActionPanel('pnlTraining', _M('Servi�os do preceptor', $module), NULL, $btnClose, $MIOLO->getUI()->getImage($module, 'preceptor-16x16.png'));
    $pnlPupil->setControlSize('100px', '70px');

    $menuItem = array();
    if ( $MIOLO->checkAccess('FrmTrainingLocation', A_ACCESS, false, true) )
    {
        $menuItem[] = array(_M('Avalia��o de est�gio', $module), 'notas-32-32.png', "main:training:trainingLocation");
    }     
    if ( $MIOLO->checkAccess('FrmMaterialRequest', A_ACCESS, false, true) )
    {
        $menuItem[] = array(_M('Solicita��o de material', $module), 'materialRequest-32x32.png', "main:materialRequest");
    }
    if ( $MIOLO->checkAccess('FrmScheduledActivity', A_ACCESS, false, true) )
    {
        $menuItem[] = array(_M('Atividade programada', $module), 'scheduledActivity-32x32.png', "main:scheduledActivity");
    }
    if ( $MIOLO->checkAccess('FrmRealizedActivity', A_ACCESS, false, true) )
    {
        $menuItem[] = array(_M('Atividade realizada', $module), 'realizedActivity-32x32.png', "main:realizedActivity");
    }
    if ( $MIOLO->checkAccess('FrmPersonalAgenda', A_ACCESS, false, true) )
    {
        $menuItem[] = array(_M('Agenda pessoal', $module), 'personalAgenda-32x32.png', "main:personalAgenda");
    }
    if ( $MIOLO->checkAccess('FrmSubscriptionServices', A_ACCESS, false, true) )
    {
        $menuItem[] = array(_M('Autoriza��o de est�gio', $module), 'preceptorTeams-32x32.png', "$home:subscription");
    }
        
    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    foreach ( $sortMenuItem as $m )
    {
        $pnlPupil->addAction($m[0], $MIOLO->getUI()->getImage($module, $m[1]), $module, $m[2], $m[3], $m[4]);
    }
    $theme->appendContent($pnlPupil);
    $sep = new MSeparator();
    $theme->appendContent($sep);
}
?>