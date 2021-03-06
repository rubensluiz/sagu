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
 * Services handler.
 * Make options available according to user profile
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 *
 * @since
 * Class created on 05/09/2007
 */

SAGU::defineUserIsFromServices();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

$home = 'main';
$module = SAGU::getFileModule(__FILE__);
$navbar->addOption(_M('Servi�os', $module), $module, $home, null, array('function' => 'resetStack'));

// Informa o formul�rio se a pessoa que est� acessando o formul�rio pelo sistema
define('USER_IS_FROM_SERVICES', DB_TRUE);

$MIOLO->getClass('basic', 'access');
$MIOLO->uses('classes/sagu.class', 'basic');

// MIOLO2 menu
include_once($MIOLO->GetConf('home.modules') . '/sagu2/handlers/menu.inc');

$ui = $MIOLO->getUI();

// Obt�m o usu�rio da pessoa logada e obt�m os dados dela
$mioloUserName = trim($MIOLO->getLogin()->id);
$busPerson = new BusinessBasicBusPerson();
$personData = $busPerson->getPersonByMioloUserName($mioloUserName);

// Acoes em que nao deve ser verificado pessoa
$passActions = array('main:trainingRequest', 'main:selectiveProcessSubscription', 'main:userRegister', 'main:moodleSubscription');

if ( is_null($personData) && ( !in_array($action, $passActions) ) && !SAGU::isDebugMode() )
{
    if( !( strlen($mioloUserName) > 0 ) )
    {
        $MIOLO->error(_M('Acesso negado.', $module));
    }
    $MIOLO->error(_M('N�o h� nenhuma pessoa associada ao usu�rio "@1".', $module, $mioloUserName));
}
else
{
    // Verifica os crach�s que deveriam ser devolvidos at� ontem
    if ( strlen($personData->personId) > 0 )
    {
        $filters = new stdClass();
        $filters->personId = $personData->personId;
        $filters->expectedReturnDateFinal = SAGU::addIntervalInDate(SAGU::getDateNow(), 'd', 1, ' - ');
        $badgeLoans = BasBadgeLoan::search($filters);

        foreach ( $badgeLoans as $badgeLoan )
        {
            $badge = new BasBadge($badgeLoan->badgeId);

            // Verifica se tem data de devolu��o
            if ( $badgeLoan->returnDate == null )
            {
                $hasBadgePending = true;
                $message .= "<br />-" . _M('Devolver o crach� @1.', $module, $badge->description);
            }
        }
    }
    
    $invoked = $MIOLO->invokeHandler($module, $context->shiftAction());

    // Se ainda n�o foi devolvido, n�o deixa acessar o portal
    if ( $hasBadgePending )
    {
        $MIOLO->error(_M('Para poder acessar o seu portal, voc� precisa:', $module) . $message);
    }
    else if ( SAGU::isAllowedAction() && ( strlen($mioloUserName) > 0 ) )
    {
        $btnClose = $MIOLO->getActionURL('sagu2', 'main');
        $pnlServices = new MActionPanel('pnlServices', _M('Servi�os', $module), NULL, $btnClose, $ui->getImage($module, 'services-16x16.png'));
        $pnlServices->setControlSize('120px', '85px');

        // Array com os menus poss�veis para a pessoa logada
        $menuItem = array();
        $services = array();

        createServicesMenu($menuItem, $services, $personData, $home);
        
        // Caso tenha acesso somente a um desses menus acima, redireciona-o diretamente para ele
        if ( count($services) == 1 )
        {
            if ( !$invoked )
            {
                $goAction = 'main:' . $services[0];
                $gotoUrl = str_replace('&amp;', '&', $MIOLO->getActionURL($module, $goAction));
                
                header('Location: ' . $gotoUrl);
            }
        }
        elseif ( count($services) == 0 && !SAGU::isAllowedAction()) // Sem acesso a nada, miolo error
        {
            //$MIOLO->error(_M('Voc� n�o est� autorizado a acessar este conte�do.', $module));
        }
        
        // Adiciona menus caso seja main ou main:professor, main:employee, etc...
        $tmpAction = str_replace('main:', '', $action);
        $inArray = in_array($tmpAction, $services);
        
        if ( $action == 'main' || $inArray )
        {
            appendServiceMenus($theme, $menuItem, $pnlServices, $ui);
        }
    }
}

function appendServiceMenus(&$theme, &$menuItem, &$pnlServices, &$ui)
{
    global $module;
    
    $sortMenuItem = SAGU::arraySort($menuItem, 0);
    
    foreach ( $sortMenuItem as $m )
    {
        $moduleAction = strlen($m[5]) > 0 ? $m[5] : $module;
        $pnlServices->addAction($m[0], $ui->getImage($module, $m[1]), $moduleAction, $m[2], $m[3], $m[4]);
    }
    
    $theme->appendContent($pnlServices);
    $sep = new MSeparator();
    $theme->appendContent($sep);
}

function createServicesMenu(&$menuItem, &$services, &$personData, $home)
{
    global $module;
    
    // Verifica se � pessoa jur�dica
    /*if ( $personData->isLegalPerson )
    {
        $menuItem[] = array(_M('Servi�o para a pessoa jur�dica', $module), 'legalPerson-48x48.png', "$home:legalPerson");
        $services[] = 'legalPerson';
    }*/

    // Verifica se � pessoa f�sica
    if ( $personData->isPhysicalPerson )
    {
        /*
            * Formul�rios para qualquer pessoa f�sica:
            */
        
        // Dados pessoais
        if ( SAGU::userHasAccess('FrmPersonalData', A_ACCESS) )
        {
            $menuItem[] = array(_M('Dados pessoais', $module), 'personalData-48x48.png', "$home:personalData");
            $services[] = '';
        }

        // Inscri��o para processo seletivo

        /*if ( SAGU::userHasAccess('FrmSelectiveProcessServices', A_ACCESS) && (SAGU::getParameter('BASIC', 'MODULE_SELECTIVEPROCESS_INSTALLED') == 'YES'))
        {
            $menuItem[] = array(_M('Inscri��o para processo seletivo', $module), 'selectiveProcess-48x48.png', "$home:selectiveProcessSubscription", null, array('function' => 'insert', 'personIdSelected' => $personData->personId));
        }*/

        // Solicita��o de est�gio
        /*if ( SAGU::userHasAccess('mainServicesTrainingRequest', A_ACCESS) && (SAGU::getParameter('BASIC', 'MODULE_TRAINING_INSTALLED') == 'YES') )
        {
            $menuItem[] = array(_M('Solicita��o de est�gio', $module), 'trainingSubscription-48x48.png', "$home:trainingRequest");
        }*/
         
        // Verifica se � um funcion�rio
        /*
        if ( $personData->isEmployee )
        {
            $menuItem[] = array(_M('Servi�os para o funcion�rio', $module), 'employee-48x48.png', "$home:employee");
            $services[] = 'employee';
        }*/

        // Verifica se � professor
        /*
        if ( $personData->isProfessor )
        {
            if ( SAGU::userHasAccess('mainServicesProfessor', A_ACCESS) )
            {
                $menuItem[] = array(_M('Servi�os do professor', $module), 'professor-48x48.png', "$home:professor");
                $services[] = 'professor';
            }

            // Verifica tamb�m se � coordenador de curso
            if ( $personData->isCourseCoordinator )
            {
                $menuItem[] = array(_M('Servi�o para coordenador de curso', $module), 'courseCoordinator-48x48.png', "$home:courseCoordinator");
                $services[] = 'courseCoordinator';
            }

            // E verifica tamb�m se � diretor de centro
            if ( $personData->isCenterDirector )
            {
                $menuItem[] = array(_M('Servi�o para diretor de centro', $module), 'centerDirector-48x48.png', "$home:centerDirector");
                $services[] = 'centerDirector';
            }
        }*/

        // Verifica se � aluno
        /*
        if ( $personData->isStudent && SAGU::userHasAccess('mainServicesStudent', A_ACCESS) )
        {
            $menuItem[] = array(_M('Servi�os para o aluno', $module), 'pupil-48x48.png', "$home:pupil");
            $services[] = 'pupil';
        }*/
        
        // Avalia��o institucional
        /*if ( SAGU::userHasAccess('frmDashboard', A_ACCESS) )
        {
            $menuItem[] = array(_M('Avalia��o institucional', 'avinst'), 'avaliacao.png', "main", null, null, 'avinst');
            $services[] = '';
        }*/
    }

    // Verifica se tem permiss�o para solicitar est�gio
    /*if ( $personData->isTraining )
    {
        $menuItem[] = array(_M('Servi�os de est�gio', $module), 'training-48x48.png', "$home:training");
        $services[] = 'training';
    }*/
        
    // Verifica se se tem permiss�o para solicitar est�gio
    /*if ( $personData->isAgreement )
    {
        $menuItem[] = array(_M('Servi�os da conveniada', $module), 'agreement-48x48.png', "$home:agreement");
        $services[] = 'agreement';
    }*/

    // Verifica se se tem permiss�o para acessar as a��es de preceptor da equipe
    if ( $personData->isTeamPreceptor )
    {
        $menuItem[] = array(_M('Servi�os do preceptor', $module), 'preceptor-48x48.png', "$home:preceptor");
        $services[] = 'preceptor';
    }

    // Verifica se pessoa � ou ja foi residente multiprofissional
    if ( $personData->isResident || $personData->isPreceptorUnidadeTematica )
    {
        $menuItem[] = array(_M('Resid�ncia multiprofissional', $module), 'residency-48x48.png', "$home:residency");
        $services[] = 'residency';
    }
    
    // Verifica se pessoa � ou j� foi residente medico
    if ( $personData->isResidentMedico || $personData->isPreceptorUnidadeTematicaMedico )
    {
        $menuItem[] = array(_M('Resid�ncia m�dica', $module), 'residency-48x48.png', "$home:resmedica");
        $services[] = 'resmedica';
    }
}
?>
