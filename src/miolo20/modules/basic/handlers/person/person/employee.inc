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
 * Basic employee handler.
 * Contains the menus to access person registers
 *
 * @author Daniel Afonso Heisler [daniel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 12/09/2005
 *
 **/

$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();
$module = MIOLO::getCurrentModule();

$navbar->addOption(_M('Funcion�rio', $module), $module, $action);
access::insert('Funcion�rio', $action, 'default-16x16.png');

if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmEmployee', A_ACCESS, true, true);

    $content = $ui->getForm($module,'FrmEmployeeSearch', $data);
    $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
}
else
{
    $MIOLO->checkAccess('FrmEmployee', A_INSERT, true, true);

    $busCenter = new BusinessAcademicBusCenter();

    $i=1;
    $steps[$i++] = new SStepInfo('FrmEmployee', _M('Funcion�rio', $module), $module);

    if ( count($busCenter->listCenter()) > 0 )
    {
        $steps[$i++] = new SStepInfo('FrmEmployeeCenter', _M('Centros', $module), $module);
    }

    $steps[$i++] = new SStepInfo('FrmFeriasFuncionario', _M('F�rias funcion�rio', $module), $module);

    $content = SStepByStepForm::getCurrentForm($steps);
}

$theme->clearContent();
$theme->insertContent($content);


?>
