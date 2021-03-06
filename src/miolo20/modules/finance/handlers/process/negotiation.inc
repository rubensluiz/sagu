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
 * Counter process handler.
 * Contains the menus to access process submenus
 *
 * @author Leovan Tavares da Silva [leovan@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Equipe Sagu [sagu@solis.coop.br]
 *
 * @since
 * Class created on 12/07/2011
 *
 **/

$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$navbar->addOption(_M('Antecipa��o / Negocia��o', $module), $module, $action);
access::insert('Antecipa��o / Negocia��o', $action, 'default-16x16.png');

//Tela de negociacao alternativa ticket #33898
$param = SAGU::getParameter('FINANCE', 'NEGOCIACAO_FORM');

if ( $param == 'FrmNegotiation' )
{
    if ( (strlen($function) == 0) || ($function == 'search') )
    {
        $MIOLO->checkAccess('FrmNegotiation', A_ACCESS, true, true);

        $content = $ui->getForm($module,'FrmNegotiationSearch', $data);
        $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
    }
    else
    {
        $MIOLO->checkAccess('FrmNegotiation', A_INSERT, true, true);

        $i=1;
        $steps[$i++] = new SStepInfo('FrmNegotiationOperation', _M('Opera��o', $module), $module);
        $steps[$i++] = new SStepInfo('FrmNegotiation', _M('Antecipa��o/ Negocia��o', $module), $module);

        $content = SStepByStepForm::getCurrentForm($steps);
    }
}
elseif ( $param == 'FrmNegotiationAlt')
{
    if ( (strlen($function) == 0) || ($function == 'search') )
    {
        $MIOLO->checkAccess('FrmNegotiation', A_ACCESS, true, true);

        $content = $ui->getForm($module,'FrmNegotiationSearch', $data);
        $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
    }
    else
    {
        $MIOLO->checkAccess('FrmNegotiation', A_INSERT, true, true);

        $content = $ui->getForm($module,'FrmNegotiationAlt', $data);
        $content->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
    }
}

$theme->clearContent();
$theme->insertContent($content);

?>
