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
 * Academic enroll handler.
 * Contains the menus to access enroll process
 *
 * @author Daniel Afonso Heisler [daniel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 13/10/2005
 *
 **/

$module = MIOLO::getCurrentModule();
$action = 'main:process:enrollContract';
$title = _M('Matr�cula', $module);
$form = SAGU::getParameter('academic', 'ENROLL_FORM');

if($form != 'FrmEnrollWeb')
{
    SAGU::handle($module, $action, $title, $form, $form, array('transactionName' => 'FrmEnrollContract'));
}
else
{
    $module = SAGU::getFileModule(__FILE__);
    $title = _M('Matr�cula', $module);
    $steps[1] = new SStepInfo('FrmEnrollWeb0', _M('Aluno', $module), 'services');
    $steps[2] = new SStepInfo('FrmEnrollWeb1', _M('Dados', $module), 'services');
    $steps[3] = new SStepInfo('FrmEnrollWeb2', _M('Disciplinas', $module), 'services');
    $steps[4] = new SStepInfo('FrmEnrollWeb3', _M('Finaliza��o', $module), 'services');

    $MIOLO = MIOLO::getInstance();
            
    $options = 'FrmEnrollWeb';
    if ( $MIOLO->getCurrentModule() == 'academic' )
    {
        $options = array('checkAccess' => true,
                         'transactionName' => 'FrmEnrollContract');
    }
    
    SAGU::handle('services', $action, $title, $searchForm, $steps, $options);
}

?>
