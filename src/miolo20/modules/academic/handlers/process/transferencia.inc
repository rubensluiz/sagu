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
 * @author Nataniel I. da Silva [nataniel@solis.com.br]
 *
 * @version $Id$
 *
 * @since
 * Class created on 08/07/2014
 */

define('TRANSFERENCIA_EM_LOTE', 'em_lote');
define('TRANSFERENCIA_UNITARIA', 'unitaria');

$module = SAGU::getFileModule(__FILE__);
$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmTransferencia', A_ADMIN, true, true);

    $content = $ui->getForm($module,'FrmTransferenciaBusca', $data);
    $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
}
else
{
    $i=1;
    $steps[$i++] = new SStepInfo('FrmTransferenciaDadosContratuais', _M('Dados contratuais', $module), $module);
    $steps[$i++] = new SStepInfo('FrmTransferenciaNotas', _M('Notas e avalia��es', $module), $module);
    $steps[$i++] = new SStepInfo('FrmTransferenciaResumo', _M('Resumo', $module), $module);

    /*SAGU::handle($module, $action, _M('Transfer�ncia de ocorr�ncia de curso', $module), null, $steps, array(
        'transactionName' => 'FrmTransferencia',
    ));
    
     * 
     */
    $content = SStepByStepForm::getCurrentForm($steps);
}

$theme->clearContent();
$theme->insertContent($content);

?>

