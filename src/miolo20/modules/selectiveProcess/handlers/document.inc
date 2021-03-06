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
 * Selective process register handler.
 * Contains the menus to access register submenus
 *
 * @author Samuel Koch [samuel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Cristian Edson G�hl [cristian@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 *
 * @since
 * Class created on 15/12/2010
 */
$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:document';
$navbar->addOption(_M('Documento/Relat�rio', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module,'document/'.$context->shiftAction()) )
{
    $MIOLO->checkAccess('sprDocument', A_ACCESS, true, true);

    $ui = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module,substr($home,0,strrpos($home,':')));

    $icon = $ui->getImage($module,'document-16x16.png');
    $pnlSelectiveProcess = new MActionPanel('pnlSelectiveProcess', _M('Documento/Relat�rio', $module), null, $btnClose, $icon);
    $pnlSelectiveProcess->setIconType('small');
    $pnlSelectiveProcess->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'),SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem = array();
    $menuItem[] = array(_M('Inscri��o',$module), 'default-16x16.png', "$home:subscription");
    $menuItem[] = array(_M('Alunos por avalia��o',$module), 'default-16x16.png', "$home:studentsByEvaluation");
    $menuItem[] = array(_M('Documentos entregues',$module), 'default-16x16.png', "$home:deliveredDocuments");
    $menuItem[] = array(_M('Lista de inscritos',$module), 'default-16x16.png', "$home:subscriptionList");
    $menuItem[] = array(_M('Estat�stica',$module), 'default-16x16.png', "$home:statistic");
    $menuItem[] = array(_M('Boletim de desempenho',$module), 'default-16x16.png', "$home:performanceBulletin");
    $menuItem[] = array(_M('Folha de resposta',$module), 'default-16x16.png', "$home:answerSheet");
    $menuItem[] = array(_M('Local de prova',$module), 'default-16x16.png', "$home:subscriptionPlace");
    $menuItem[] = array(_M('Ata de exame',$module), 'default-16x16.png', "$home:examAct");
    $menuItem[] = array(_M('Lista de candidatos por curso',$module), 'default-16x16.png', "$home:subscribersByCourse");
    $menuItem[] = array(_M('Resultado final',$module), 'default-16x16.png', "$home:finalResult");
    $menuItem[] = array(_M('Resultado em etapas',$module), 'default-16x16.png', "$home:resultadoEmEtapa");
	$menuItem[] = array(_M('Lista de aprovados por op��o de curso',$module), 'default-16x16.png', "$home:approvedListByCourse");
	$menuItem[] = array(_M('Pagos/N�o pagos',$module), 'default-16x16.png', "$home:pagosNaoPagos");
	$menuItem[] = array(_M('Lista de aprovados',$module), 'default-16x16.png', "$home:approvedList");
    $menuItem[] = array(_M('Lista de candidatos com necessidades especiais',$module), 'default-16x16.png', "$home:subscribersBySpecialNecessity");
    $menuItem = array_merge( SAGU::getGenericReportsMenu('SELECTIVEPROCESS'), $menuItem );

    $menuItem = SAGU::arraySort($menuItem, 0);
    
    $MIOLO->uses('classes/breport.class','base');
    $breport = new BReport();
    foreach($breport->listReports(BReport::TYPE_ALL,$module) as $report)
    {
        $menuItem[] = array(_M($report['title'].'*', $module), 'default-16x16.png', "$home:generateReport&report={$report['name']}");
    }
    
    foreach ( $menuItem as $m )
    {
       $pnlSelectiveProcess->addUserAction('sprDocument', A_ACCESS, $m[0], $ui->getImage($module,$m[1]), $module, $m[2], null, $m[4]);
    }

    $theme->clearContent();
    $theme->insertContent($pnlSelectiveProcess);
}
?>