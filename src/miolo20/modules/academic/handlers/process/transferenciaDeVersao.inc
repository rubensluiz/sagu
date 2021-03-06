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
 * @author Augusto A. Silva [augusto@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Augusto A. Silva [augusto@solis.coop.br]
 *
 * @since
 * Class created on 06/09/2013
 */
define('TRANSFERENCIA_EM_LOTE', 'em_lote');
define('TRANSFERENCIA_UNITARIA', 'unitaria');

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$module = $MIOLO->getCurrentModule();
$action = 'main:process:transferenciaDeVersao';

$navbar->addOption(_M('Transfer�ncia de vers�o de curso', $module), $module, $action);
access::insert('Transfer�ncia de vers�o curso', $action, 'default-16x16.png');

//Checa as permiss�es
$MIOLO->checkAccess('FrmTransferenciaDeVersao', A_EXECUTE, true, true);

$i=1;
$steps[$i++] = new SStepInfo('FrmTransferenciaDeVersaoDadosContratuais', _M('Dados contratuais', $module), $module);
$steps[$i++] = new SStepInfo('FrmTransferenciaDeVersaoResumo',  _M('Resumo', $module), $module);

$content = SStepByStepForm::getCurrentForm($steps);

$theme->clearContent();
$theme->insertContent($content);
?>