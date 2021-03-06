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
 * @author Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 *
 * @since
 * Class created on 13/04/2011
 */

$home = 'main:residency';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�os de resid�ncia multiprofissional', $module), $module, $home, null, array('function' => 'resetStack'));

if ( !$MIOLO->invokeHandler($module, 'residency/' . $context->shiftAction()) )
{
    $btnClose = $MIOLO->getActionURL('sagu2', 'main');
    $pnlPupil = new MActionPanel('pnlResidency', _M('Servi�os de resid�ncia multiprofissional', $module), NULL, $btnClose, $MIOLO->getUI()->getImage($module, 'training-16x16.png'));
    $pnlPupil->setControlSize('100px', '70px');

    // Obt�m o usu�rio da pessoa logada e obt�m os dados dela
    $mioloUserName = trim($MIOLO->getLogin()->id);
    $busPerson = new BusinessBasicBusPerson();
    $personData = $busPerson->getPersonByMioloUserName($mioloUserName);

    unset($menuItem);
    $menuItem = array();
    
    // Verifica se pessoa � ou ja foi  preceptor de unidade tematica
    if ( $personData->isPreceptorUnidadeTematica )
    {
        $menuItem[] = array(_M('Consulta de assiduidade', $module), 'residencyPreceptor-32x32.png', "$home:unidadesTematicasDoPreceptor");
    }
    // Verifica se a pessoa � residente
    if ( $personData->isResident )
    {
        $menuItem[] = array(_M('Consulta de assiduidade', $module), 'residente-32x32.png', "$home:consultaDoResidente");
        $menuItem[] = array(_M('Trabalho de Conclus�o', $module), 'icone-tcc.png', "$home:trabalhoConclusao");
    }

    if ( $personData->responsavelNucleoEnfase )
    {
        $menuItem[] = array(_M('Residentes e notas', $module), 'notas-32-32.png', "$home:digitacaoDeNotas");
    }

    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    foreach ( $sortMenuItem as $m )
    {
        $imageURL = $MIOLO->getActionURL( 'services', "html:images:{$m[1]}" );
        
        $pnlPupil->addAction($m[0], $imageURL, $module, $m[2], $m[3], $m[4]);
    }
    $theme->appendContent($pnlPupil);
    $sep = new MSeparator();
    $theme->appendContent($sep);
}
?>