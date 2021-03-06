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
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 *
 * @since
 * Class created on 05/09/2007
 */

$home = 'main:legalPerson';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�o para a pessoa jur�dica', $module), $module, $home, null, array('function' => 'resetStack'));

// Obt�m o usu�rio da pessoa logada e obt�m os dados dela
$mioloUserName = trim($MIOLO->getLogin()->id);
$busPerson = new BusinessBasicBusPerson();
$personData = $busPerson->getPersonByMioloUserName($mioloUserName);

if ( !$busPerson->isPersonLegal($personData->personId) )
{
    $MIOLO->error(_M('Voc� deve ser pessoa jur�dica para acessar este conte�do.', $module));
}
elseif ( !$MIOLO->invokeHandler($module, 'legalPerson/' . $context->shiftAction()) )
{
    $btnClose = $MIOLO->getActionURL('sagu2', 'main');

    if ( is_null($personData) )
    {
        $MIOLO->error(_M('N�o foi poss�vel obter os dados do usu�rio @1.', $module, $mioloUserName));
    }
    else
    {
        $pnlLegalPerson = new MActionPanel('pnlLegalPerson', _M('Pessoa jur�dica', $module), NULL, $btnClose, $MIOLO->getUI()->getImage($module, 'legalPerson-16x16.png'));
        $pnlLegalPerson->setControlSize('100px', '70px');

        unset($menuItem);
        $menuItem[] = array(_M('Dados pessoais', $module), 'personalData-32x32.png', "$home:personalData");
        $menuItem[] = array(_M('Defini��o de avalia��es', $module), 'evaluationDefinition-32x32.png', "$home:evaluationDefinition");
        $menuItem[] = array(_M('Material impresso', $module), 'printedMaterial-32x32.png', "$home:printedMaterial");
        $menuItem[] = array(_M('Links externos', $module), 'externalLinks-32x32.png', "$home:externalLinks");
        $menuItem[] = array(_M('Hor�rio', $module), 'schedule-32x32.png', "$home:schedule");
        $menuItem[] = array(_M('Disciplinas', $module), 'curricularComponents-32x32.png', "$home:curricularComponents");

        $sortMenuItem = SAGU::arraySort($menuItem, 0);
        foreach ( $sortMenuItem as $m )
        {
            $pnlLegalPerson->addAction($m[0], $MIOLO->getUI()->getImage($module, $m[1]), $module, $m[2], $m[3]);
        }
        $theme->appendContent($pnlLegalPerson);
        $sep = new MSeparator();
        $theme->appendContent($sep);
    }
}
?>