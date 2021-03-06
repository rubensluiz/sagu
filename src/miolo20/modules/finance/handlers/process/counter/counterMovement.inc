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
 * Finance counterMovement handler.
 * Contains the menus to access counterMovement registers
 *
 * @author Armando Taffarel Neto [taffarel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @since
 * Class created on 03/01/2006
 *
 * */
$module = MIOLO::getCurrentModule();
$action = "main:process:counter:counterMovement";
$title = _M("Caixa", $module);
$form = "FrmCounterMovement";
$acao = MIOLO::_REQUEST("acao");

$login = $MIOLO->GetLogin();
$busPhysicalPersonEmployee = $MIOLO->getBusiness('basic', 'BusPhysicalPersonEmployee');
$pessoaLogada = $busPhysicalPersonEmployee->getPersonByMioloUserName($login->id);

$caixa = null;

if ( is_object($pessoaLogada) )
{
    $busOpenCounter = $MIOLO->getBusiness($module, 'BusOpenCounter');
    $busCounter = $MIOLO->getBusiness($module, 'BusCounter');

    // Filtros para a pessoa que est� tentando acessar
    $filtro = new stdClass();
    $filtro->operatorId = $pessoaLogada->personId;
    $filtro->open = 't';

    $pesquisaOpenCounter = $busOpenCounter->searchOpenCounter($filtro);
    
    if ( is_array($pesquisaOpenCounter) )
    {
        $caixaEmAberto = $busOpenCounter->getOpenCounter($pesquisaOpenCounter[0][0]);
        $caixa = $busCounter->getCounter($caixaEmAberto->counterId);    
    }
}

$EhCaixaTesouraria = $caixa->isCounterTreasury === DB_TRUE;
$CAPEstaHabilitado = SAGU::getParameter("basic", "MODULE_CONTASPAGAR_INSTALLED") === "YES";

if ( ( ( (strlen($acao) === 0 || ($acao === "pagar" ) ) && $EhCaixaTesouraria ) ) && $CAPEstaHabilitado && ( strstr($MIOLO->getCurrentURL(), "acao=receber") === false ) )
{
    $form = "FrmCounterMovementPagar";
}
else
{
    $form = "FrmCounterMovement";
}

$ui = $MIOLO->getUI();
$navbar->addOption($title, $module, $action);
$content = $ui->getForm($module, $form);

if ( $theme->page->generateMethod != "generateAjax" )
{
    $theme->clearContent();
    $theme->insertContent($content);
}

?>
