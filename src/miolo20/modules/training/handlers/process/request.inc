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
 * @author Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @since
 * Class created on 30/03/2011
 *
 **/
$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$navbar->addOption(_M('Solicita��o de est�gio', $module), $module, $action);
access::insert('Solicita��o de est�gio', $action, 'default-16x16.png');

// faz checkAccess somente se login.check for true
// serve para nao fazer o checkAccess quando estiver via modulo services
if ( $MIOLO->getConf('login.check') == 'true' )
{
    switch ( $function )
    {
        case 'insert':
            $MIOLO->checkAccess('FrmStageRequest', A_INSERT, true, true);
        break;
        case 'update':
            if (strlen(MIOLO::_request('event')) > 0 || $_POST['__EVENTTARGETVALUE'] == 'btnSave:click')
            {
                $MIOLO->checkAccess('FrmStageRequest', A_UPDATE, true, true);
            }
            else
            {
                $MIOLO->checkAccess('FrmStageRequest', A_ACCESS, true, true);
            }
        break;
        case 'delete':
            $MIOLO->checkAccess('FrmStageRequest', A_DELETE, true, true);
        break;
    }
}

$steps = SAGU::getTrainingRequestSteps();
$content = SStepByStepForm::getCurrentForm($steps);

$theme->clearContent();
$theme->insertContent($content);
?>