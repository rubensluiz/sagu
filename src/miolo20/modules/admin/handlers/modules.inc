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
 *
 * This file modules
 *
 * @author Leovan Tavares da Silva [leovan] [leovan@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Leovan Tavares da Silva [leovan@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * 
 * @since
 * Class created on 14/06/2006
 *
 **/
$MIOLO->trace('file:'.$_SERVER['SCRIPT_NAME']);

$MIOLO->checkAccess('admin',A_ACCESS,true);

$navbar->addOption( _M('Modules', $module) ,$module, 'main:modules');

$ui = $MIOLO->getUI();

$theme->clearContent();

$close = $MIOLO->getActionURL($module,'main');

$cmPanel = new ActionPanel('pnlAdmin', _M('Modules Maintainance',$module),'', $close, $ui->getImage($module,'modules-16x16.png') );

$cmPanel->addAction( _M('Editar m�dulo', $module)      , $ui->getImage($module, 'module_edit-32x32.png'), $module, 'main:modules:edit_modules');
$cmPanel->addAction( _M('Instalar novo modulo', $module), $ui->getImage($module, 'module_add-32x32.png'), $module, 'main:modules:modules_new');
$cmPanel->addAction( _M('Remover modulos', $module)    , $ui->getImage($module, 'module_del-32x32.png'), $module, 'main:modules:rem_modules');

$handled = $MIOLO->invokeHandler($module,'modules/'.$context->shiftAction() );

if ( ! $handled )
{
    $theme->insertContent($cmPanel);
}
