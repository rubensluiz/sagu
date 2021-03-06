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
 * @author Moises Heberle [moises@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * Moises Heberle [moises@solis.coop.br]
 *
 * @since
 * Class created on 20/12/2010
 */

$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$navbar->addOption(_M('Processo seletivo', $module), $module, $action);
access::insert('Processo seletivo', $action, 'default-16x16.png');

if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmSelectiveProcess', A_ACCESS, true, true);

    $content = $ui->getForm($module, 'FrmSelectiveProcessSearch', $data);
    $content->setClose($MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':'))));
}
else
{
    switch ( $function )
    {
        case 'insert':
            $MIOLO->checkAccess('FrmSelectiveProcess', A_INSERT, true, true);
        break;
        case 'update':
            if ( strlen(MIOLO::_request('event')) > 0 || $_POST['__EVENTTARGETVALUE'] == 'btnSave:click' )
            {
                $MIOLO->checkAccess('FrmSelectiveProcess', A_UPDATE, true, true);
            }
            else
            {
                $MIOLO->checkAccess('FrmSelectiveProcess', A_ACCESS, true, true);
            }
        break;
        case 'delete':
            $MIOLO->checkAccess('FrmSelectiveProcess', A_DELETE, true, true);
        break;
    }

    $i = 1;
    if ( $function != SForm::FUNCTION_UPDATE ) //No editar, pula o passo 1
    {
        $steps[$i++] = new SStepInfo('FrmSelectiveProcessChooser', _M('Escolha do processo seletivo', $module));
    }
    $steps[$i++] = new SStepInfo('FrmSelectiveProcess', _M('Processo seletivo', $module), $module);
    $steps[$i++] = new SStepInfo('FrmOptionCourse', _M('Op��es de curso', $module), $module);
    $steps[$i++] = new SStepInfo('FrmStep', _M('Etapa', $module), $module);
    $steps[$i++] = new SStepInfo('FrmFinanceInformation', _M('Taxa de vestibular', $module), $module);

    $content = SStepByStepForm::getCurrentForm($steps);
}

$theme->clearContent();
$theme->insertContent($content);
?>