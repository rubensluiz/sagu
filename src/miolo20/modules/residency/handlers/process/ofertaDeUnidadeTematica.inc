<?php
/**
 * <--- Copyright 2005-2011 de Solis - Cooperativa de Solu��es Livres Ltda.
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
 * @author Moises Heberle [moises@solis.coop.br]
 *
 * \b Maintainers \n
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Moises Heberle [moises@solis.coop.br]
 * Lu�s Felipe Wermann [luis_felipe@solis.com.br]
 *
 * @since
 * Class created on 16/07/2011
 */

ini_set('max_execution_time', 3000);
ini_set('memory_limit', '-1');

$module = SAGU::getFileModule(__FILE__);
$action = MIOLO::getCurrentAction();
$title = _M('Oferta de unidade tem�tica', $module);
$searchForm = 'FrmOfertaDeUnidadeTematicaSearch';

//Etapas
$steps[1] = new SStepInfo('FrmOfertaDeUnidadeTematica', _M('Oferta de unidade tem�tica', $module), $module);
$steps[2] = new SStepInfo('FrmOfertaDeUnidadeTematicaEncontros', _M('Encontros da oferta', $module), $module);

SAGU::handle($module, $action, $title, $searchForm, $steps, array('transactionName' => 'FrmOfertaDeUnidadeTematica', 'checkAccess' => true));
?>