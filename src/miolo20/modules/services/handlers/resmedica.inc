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
 * @author Lu�s Felipe Wermann [luis_felipe@solis.com.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Lu�s Felipe Wermann [luis_felipe@solis.com.br]
 *
 * @since
 * Class created on 24/11/2014
 */

$home = 'main:resmedica';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�os de resid�ncia m�dica', $module), $module, $home, null, array('function' => 'resetStack'));

if ( !$MIOLO->invokeHandler($module, 'resmedica/' . $context->shiftAction()) )
{
    $btnClose = $MIOLO->getActionURL('sagu2', 'main');
    $pnlPupil = new MActionPanel('pnlResidency', _M('Servi�os de resid�ncia m�dica', $module), NULL, $btnClose, $MIOLO->getUI()->getImage($module, 'training-16x16.png'));
    $pnlPupil->setControlSize('100px', '70px');

    // Obt�m o usu�rio da pessoa logada e obt�m os dados dela
    $mioloUserName = trim($MIOLO->getLogin()->id);
    $busPerson = new BusinessBasicBusPerson();
    $personData = $busPerson->getPersonByMioloUserName($mioloUserName);

    unset($menuItem);
    $menuItem = array();

    // Verifica se pessoa � ou ja foi  preceptor de unidade tematica
    if ( $personData->isPreceptorUnidadeTematicaMedico )
    {
        $menuItem[] = array(_M('Consulta do preceptor', $module), 'residencyPreceptor-32x32.png', "$home:unidadesTematicasDoPreceptor");
    }
    // Verifica se a pessoa � residente
    if ( $personData->isResidentMedico)
    {
        $menuItem[] = array(_M('Consulta do residente', $module), 'residente-32x32.png', "$home:consultaDoResidente");
        $menuItem[] = array(_M('Di�rio de campo', $module), 'diario-32x32.png', "$home:diarioDeCampo");
        $menuItem[] = array(_M('Autoavalia��o e parecer do programa', $module), 'autoavaliacao-32x32.png', "$home:autoAvaliacao");
    }
    if ( SAGU::getParameter('BASIC', 'MODULE_SERVICES_INSTALLED') == 'YES')
    {
        if ( $personData->isResidentMedico)
        {
            $menuItem[] = array(_M('Solicita��o de protocolo', $module), 'residency-32x32.png', "$home:protocolo");
        }

        if ( $personData->isResidentMedico )
        {
            $menuItem[] = array(_M('Trabalho de Conclus�o', $module), 'icone-tcc.png', "$home:trabalhoConclusao");
        }

    }
    /*
    if ( $personData->responsavelNucleoEnfaseMedico )
    {
        $menuItem[] = array(_M('Digita��o de notas', $module), 'notas-32-32.png', "$home:digitacaoDeNotas");
    }*/

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