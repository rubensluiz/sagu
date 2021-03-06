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
 * Finance register handler.
 * Contains the menus to access geography submenus
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Eduardo Beal Miglioransa [eduardo@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 17/08/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('finRegister', A_ACCESS, true, true);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

$home = 'main:register';
$navbar->addOption(_M('Cadastro', $module), $module, $home, null, array('function'=>'resetStack'));

if ( !$MIOLO->invokeHandler($module,'register/'.$context->shiftAction()) )
{
    $ui       = $MIOLO->getUI();
    $btnClose = $MIOLO->getActionURL($module,substr($home,0,strrpos($home,':')));

    $icon        = $ui->getImage($module,'register-16x16.png');
    $pnlRegister = new MActionPanel('pnlRegister', _M('Cadastro', $module), NULL, $btnClose, $icon);
    $pnlRegister->setIconType('small');
    $pnlRegister->setControlSize(SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_WIDTH'),SAGU::getParameter('BASIC', 'MPANEL_DEFAULT_HEIGHT'));

    $menuItem = array( array(_M('Conta banc�ria',        $module), 'bankAccount-16x16.png',       "$home:bankAccount"),
                       array(_M('Banco',                $module), 'bank-16x16.png',              "$home:bank"),
                       array(_M('Conta para d�bito autom�tico',         $module), 'invoiceTarget-16x16.png',     "$home:bankTarget"),
                       array(_M('Tipo de cobran�a',     $module), 'collectionType-16x16.png',    "$home:collectionType"),
                       array(_M('Opera��o',           $module), 'operation-16x16.png',         "$home:operation"),
                       array(_M('Pol�tica',              $module), 'policy-16x16.png',            "$home:policy"),
                       array(_M('Pre�o',               $module), 'price-16x16.png',             "$home:price"),
                       array(_M('T�tulo',             $module), 'folder-16x16.png',            "$home:invoice", null, array('function'=>'resetStack')),
                       array(_M('Esp�cie',             $module), 'species-16x16.png',           "$home:species"),
                       array(_M('Origem',       $module), 'incomeSource-16x16.png',      "$home:incomeSource"),
                       array(_M('Previs�o de lan�amento',     $module), 'incomeForecast-16x16.png',    "$home:incomeForecast"),
                       array(_M('Mensagens para os demonstrativos financeiros',    $module), 'voucherMessages-16x16.png',   "$home:voucherMessages"),
                       array(_M('Caixa',             $module), 'counter-16x16.png',           "$home:counter"),
                       array(_M('Taxa de matr�cula',          $module), 'enrollFee-16x16.png',         "$home:enrollFee"),
                       array(_M('Lan�amento',               $module), 'entry-16x16.png',             "$home:entry"),
                       array(_M('Opera��es padr�o',  $module), 'defaultOperations-16x16.png', "$home:defaultOperations"),
                       array(_M('Endere�o de cobran�a',     $module), 'physicalTarget-16x16.png',    "$home:physicalTarget"),
                       array(_M('Motivo do cancelamento', $module), 'reasonCancellation-16x16.png', "$home:reasonCancellationFinance"),
		       array(_M('Conv�nio da pessoa',    $module), 'convenantPerson-16x16.png',   "$home:convenantPerson"),
                       array(_M('Tipo de incentivo',      $module), 'folder-16x16.png',            "$home:incentiveType", null, array('function'=>'resetStack')),
                       array(_M('Incentivo',           $module), 'incentive-16x16.png',         "$home:incentive"),
                       array(_M('Grupo de opera��es',     $module), 'operationGroup-16x16.png',    "$home:operationGroup"),
                       array(_M('FIES retroativo',   $module), 'studentFinancing-16x16.png',  "$home:studentFinancing")
                     );

    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    foreach ( $sortMenuItem as $m )
    {
       $pnlRegister->addAction($m[0], $ui->getImage($module,$m[1]), $module, $m[2], $m[3], $m[4]);
    }

    $theme->clearContent();
    $theme->insertContent($pnlRegister);
}

?>
