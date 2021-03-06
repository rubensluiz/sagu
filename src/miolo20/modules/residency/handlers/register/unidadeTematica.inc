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
 *
 * Handler do formul�rio de unidade tem�tica
 *
 * @author Arthur Lehdermann [arthur@solis.coop.br]
 *
 * \b Maintainers \n
 * Arthur Lehdermann [arthur@solis.coop.br]
 *
 * @since
 * Class created on 15/07/2011
 */

$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$navbar->addOption(_M('Unidade tem�tica', $module), $module, $action);
access::insert('Unidade tem�tica', $action, 'default-16x16.png');

if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmUnidadeTematica', A_ACCESS, true, true);

    $content = $ui->getForm($module,'FrmUnidadeTematicaSearch', $data);
    $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
}
elseif ( $function == 'update' || $function == 'delete' )
{
    if (strlen(MIOLO::_request('event')) > 0 || $_POST['__EVENTTARGETVALUE'] == 'btnSave:click')
    {
        $MIOLO->checkAccess('FrmUnidadeTematica', A_UPDATE, true, true);
    }
    else
    {
        $MIOLO->checkAccess('FrmUnidadeTematica', A_ACCESS, true, true);
    }

    $content = $ui->getForm($module,'FrmUnidadeTematicaEdicao', $data);
    $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
}
else // insert
{
    $MIOLO->checkAccess('FrmUnidadeTematica', A_INSERT, true, true);

    $i=1;
    $steps[$i++] = new SStepInfo('FrmUnidadeTematicaDadosGerais', _M('Dados gerais', $module), $module);
    $steps[$i++] = new SStepInfo('FrmUnidadeTematicaNucleosProfissionais', _M('N�cleos profissionais'), $module);
    $steps[$i++] = new SStepInfo('FrmUnidadeTematicaEnfases', _M('�nfases'), $module);

    $content = SStepByStepForm::getCurrentForm($steps);
}

$theme->clearContent();
$theme->insertContent($content);
?>