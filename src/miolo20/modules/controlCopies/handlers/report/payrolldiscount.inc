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
 * Control copy reports handler.
 *
 * @author Rafael Diutra [rdutra@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Rafael Dutra [rdutra@solis.coop.br]
 * Rafael Lu�s Spengler [rafael@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 23/08/2006
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess('FrmPayRollDiscountReport', A_ACCESS, true, true);

$home = 'main:report:payrolldiscount';
$navbar->addOption(_M('Desconto em folha', $module), $module, $home);

$MIOLO->getClass('basic', 'access');
access::insert(_M('Desconto em folha', $module), $home, 'payrolldiscount-16x16.png');
$data->home = $home;

$function = MIOLO::_request('function');

$ui = $MIOLO->getUI();

$frmPayRollDiscountReport = $ui->getForm($module,'FrmPayRollDiscountReport', $data);
$frmPayRollDiscountReport->setClose($MIOLO->getActionURL($module, substr($home, 0, strrpos($home, ':'))));
$content = $frmPayRollDiscountReport;

$theme->clearContent();
$theme->insertContent($content);

?>
