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
 * Professor services handler.
 * Used to access the professor services
 *
 * @author Arthur Lehdermann [arthur@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Arthur Lehdermann [arthur@solis.coop.br]
 *
 * @since
 * Class created on 15/06/2011
 */

$home = 'main:courseCoordinator';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�os do coordenador de curso', $module), $module, $home, null, array('function' => 'resetStack'));

// Obt�m o usu�rio da pessoa logada e obt�m os dados dela
$mioloUserName = trim($MIOLO->getLogin()->id);
$busPerson = $MIOLO->getBusiness('basic', 'BusPerson');
$personData = $busPerson->getPersonByMioloUserName($mioloUserName);

if ( !$personData->isCourseCoordinator )
{
    $MIOLO->error(_M('Voc� deve ser coordenador de algum curso para acessar este conte�do.', $module));
}
elseif ( !$MIOLO->invokeHandler($module, 'courseCoordinator/' . $context->shiftAction()) )
{
    $btnClose = $MIOLO->getActionURL('sagu2', 'main');

    if ( is_null($personData) )
    {
        $MIOLO->error(_M('N�o foi poss�vel obter os dados do usu�rio @1.', $module, $mioloUserName));
    }
    else
    {
        $pnlCourseCoordinator = new MActionPanel('pnlCourseCoordinator', _M('Coordenador de curso',$module), NULL, $btnClose, $MIOLO->getUI()->getImage($module, 'courseCoordinator-16x16.png'));
        $pnlCourseCoordinator->setControlSize('100px', '70px');

        unset($menuItem);
        $menuItem[] = array(_M('Solicita��o de material', $module), 'materialRequest-32x32.png', "main:materialRequest");
        $menuItem[] = array(_M('Atividade programada', $module), 'scheduledActivity-32x32.png', "main:scheduledActivity");
        $menuItem[] = array(_M('Atividade realizada', $module), 'realizedActivity-32x32.png', "main:realizedActivity");
        $menuItem[] = array(_M('Planilha de horas do coordenador de curso', $module), 'courseCoordinatorSheet-32x32.png', "$home:courseCoordinatorSheet");
        $menuItem[] = array(_M('Agenda pessoal', $module), 'personalAgenda-32x32.png', "main:personalAgenda");

        $sortMenuItem = SAGU::arraySort($menuItem, 0);
        foreach ( $sortMenuItem as $m )
        {
            $pnlCourseCoordinator->addAction($m[0], $MIOLO->getUI()->getImage($module, $m[1]), $module, $m[2], $m[3]);
        }
        $pnlCourseCoordinator->addAction('Voltar', $MIOLO->getUI()->getImage($module, 'back-32x32.png'), $module,'main:services');

        $theme->appendContent($pnlCourseCoordinator);
        $sep = new MSeparator();
        $theme->appendContent($sep);
    }
}
?>
