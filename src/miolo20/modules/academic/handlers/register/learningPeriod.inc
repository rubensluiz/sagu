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
 * Basic learningPeriod handler.
 * Contains the menus to access learningPeriod registers
 *
 * @author Jamiel Spezia [jamiel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Jonas Gualberto Diel [jonas_diel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @since
 * Class created on 25/08/2005
 *
 **/
$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$navbar->addOption(_M('Per�odo letivo', $module), $module, $action);
access::insert('Per�odo letivo', $action, 'default-16x16.png');

if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmLearningPeriod', A_ACCESS, true, true);

    $content = $ui->getForm($module,'FrmLearningPeriodSearch', $data);
    $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
}
else
{
    switch ( $function )
    {
        case 'insert':
            $MIOLO->checkAccess('FrmLearningPeriod', A_INSERT, true, true);
        break;
        case 'update':
            if (strlen(MIOLO::_request('event')) > 0 || $_POST['__EVENTTARGETVALUE'] == 'btnSave:click')
            {
                $MIOLO->checkAccess('FrmLearningPeriod', A_UPDATE, true, true);
            }
            else
            {
                $MIOLO->checkAccess('FrmLearningPeriod', A_ACCESS, true, true);
            }
        break;
        case 'delete':
            $MIOLO->checkAccess('FrmLearningPeriod', A_DELETE, true, true);
        break;
    }

    $i=1;
    $steps[$i++] = new SStepInfo('FrmLearningPeriodChooser', _M('Escolha do per�odo letivo anterior', $module));
    $steps[$i++] = new SStepInfo('FrmLearningPeriodGeneralData',  _M('Dados gerais', $module), $module);
    $steps[$i++] = new SStepInfo('FrmLearningPeriodFrequenceAndNote',  _M('Frequ�ncia e notas', $module), $module);
    $steps[$i++] = new SStepInfo('FrmLearningPeriodLimits',  _M('Limites', $module), $module);
    $steps[$i++] = new SStepInfo('FrmLearningPeriodFinance',  _M('Financeiro', $module), $module);

    $content = SStepByStepForm::getCurrentForm($steps);
}

$theme->clearContent();
$theme->insertContent($content);

?>