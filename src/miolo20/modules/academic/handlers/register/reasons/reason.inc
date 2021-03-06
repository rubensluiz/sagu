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
 * Reason handler.
 * Contains the menus to access reason registers
 *
 * @author Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
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
 * Class created on 15/09/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

$home = 'main:register:reasons:reason';
$navbar->addOption(_M('Motivo', $module), $module, $home);

$MIOLO->getClass('basic', 'access');
access::insert(_M('Motivo', $module), $home, 'reason-16x16.png');
$data->home = $home;

$function = MIOLO::_request('function');

$ui = $MIOLO->getUI();
if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmReason', A_ACCESS, true, true);
    
    $frmReasonSearch = $ui->getForm($module,'FrmReasonSearch', $data);
    $frmReasonSearch->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));

    $content = $frmReasonSearch;
}
else
{
    switch ( $function )
    {
        case 'insert':
            $MIOLO->checkAccess('FrmReason', A_INSERT, true, true);
        break;
        case 'update':
            if (strlen(MIOLO::_request('event')) > 0)
            {
                $MIOLO->checkAccess('FrmReason', A_UPDATE, true, true);
            }
            else
            {
                $MIOLO->checkAccess('FrmReason', A_ACCESS, true, true);
            }
        break;
        case 'delete':
            $MIOLO->checkAccess('FrmReason', A_DELETE, true, true);
        break;
    }
          
    $frmReason = $ui->getForm( $module, 'FrmReason' );

    $content = $frmReason;
}

$theme->clearContent();
$theme->insertContent($content);

?>
