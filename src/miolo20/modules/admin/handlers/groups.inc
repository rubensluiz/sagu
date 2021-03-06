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
 * This file groups
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

#FIXME: Utilizar por enquanto, futuramente esta tela sera alterada
//para usar 1gb no formul�rio de permissoes
ini_set('memory_limit', '1024M');
//aumenta o tamanho maximo de post de itens
ini_set('max_input_vars', 5000);

$home = 'main:groups';
$navbar->AddOption(_M('Grupos',$module),$module,$self);
$ui = $MIOLO->GetUI();

$function = MIOLO::_REQUEST('function');
$data->home = $home;

if ($function == 'insert' || $function == 'update' || $function == 'delete')
{
    $MIOLO->checkAccess('frmGroup', A_ADMIN, true, true);
    $content = $ui->GetForm($module,'frmGroup');
}
else
{
    $MIOLO->checkAccess('frmGroup', A_ADMIN, true, true);
    $content = $ui->GetForm($module,'frmGroupSearch', $data);
}

//Theme receives the contents of the form
if ($theme->page->generateMethod != 'generateAjax')
{
    $theme->clearContent();
    $theme->insertContent($content);
}

?>
