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
 * LegalPerson services handler.
 * Used to access the legalPerson services
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 *
 * @since
 * Class created on 15/04/2011
 */

$home = 'main:agreement';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�o da conveniada', $module), $module, $home, null, array('function' => 'resetStack'));

// Obt�m o usu�rio da pessoa logada e obt�m os dados dela
$mioloUserName = trim($MIOLO->getLogin()->id);
$busPerson = new BusinessBasicBusPerson();
$personData = $busPerson->getPersonByMioloUserName($mioloUserName);

$isAgreement = TraAddendumCourseAdmin::isAgreement($personData->personId);
if ( !$isAgreement )
{
    $MIOLO->error(_M('Voc� n�o � uma pessoa conveniada para acessar este conte�do.', $module));
}
elseif ( !$MIOLO->invokeHandler($module, 'agreement/' . $context->shiftAction()) )
{
    $btnClose = $MIOLO->getActionURL('sagu2', 'main');

    if ( is_null($personData) )
    {
        $MIOLO->error(_M('N�o foi poss�vel obter os dados do usu�rio @1.', $module, $mioloUserName));
    }
    else
    {
        $pnlAgreement = new MActionPanel('pnlAgreement', _M('Conveniada', $module), NULL, $btnClose, $MIOLO->getUI()->getImage($module, 'agreement-16x16.png'));
        $pnlAgreement->setControlSize('100px', '70px');

        unset($menuItem);
        $menuItem[] = array(_M('Solicita��o em massa', $module), 'personalData-32x32.png', "$home:trainingRequests");
        $menuItem[] = array(_M('Hist�rico de Est�gios', $module), 'training-32x32.png', "main:training:requestHistory");
        $menuItem[] = array(_M('Listar solicita��es', $module), 'materialRequest-32x32.png', "$home:listRequests");

        $sortMenuItem = SAGU::arraySort($menuItem, 0);
        foreach ( $sortMenuItem as $m )
        {
            $pnlAgreement->addAction($m[0], $MIOLO->getUI()->getImage($module, $m[1]), $module, $m[2], $m[3]);
        }

        $theme->appendContent($pnlAgreement);
        $sep = new MSeparator();
        $theme->appendContent($sep);
    }
}
?>