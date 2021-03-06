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
 * Matricula Web.
 *
 * @author Jonas Guilherme Dahmer [jonas@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Equipe Solis [sagu2@solis.coop.br]
 *
 * @since
 * Class created on 09/04/2012
 */

$module = SAGU::getFileModule(__FILE__);
$action = 'main:wnrollWeb';
$title = _M('Matr�cula Web', $module);
$steps[1] = new SStepInfo('FrmEnrollWeb1', _M('Dados', $module), $module);
$steps[2] = new SStepInfo('FrmEnrollWeb2', _M('Disciplinas', $module), $module);
$steps[3] = new SStepInfo('FrmEnrollWeb3', _M('Finaliza��o', $module), $module);

SAGU::handle($module, $action, $title, $searchForm, $steps, 'FrmEnrollWeb', true);
?>