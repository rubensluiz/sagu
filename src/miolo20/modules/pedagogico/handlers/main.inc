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
 * Class Handler Pedagogico
 *
 * @author Jonas Gualberto Diel [jonas_diel@solis.com.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Jonas Gualberto Diel [jonas_diel@solis.com.br]
 *
 * @since
 * Class created on 14/06/2006
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);

$function = MIOLO::_request('function');
if ( $function == 'resetStack' )
{
    SAGU::resetStack();
}

//MIOLO2 menu
include_once($MIOLO->GetConf('home.modules') .'/sagu2/handlers/menu.inc');

// Inclui o manipulador.
$type = MIOLO::_REQUEST("type", "GET");

if ( strlen($type) > 0 )
{
    $MIOLO->uses('handlers/manipulador.inc.php', 'base');
}
else
{
    $ui = $MIOLO->getUI();

    if ( !SAGU::invokeHandlerAuto() )
    {
        $MIOLO->checkAccess('PEDAGOGICO', A_ACCESS, true, true);

        $a = new Separator();
        $frmDiverseConsultation = $ui->getForm($module, 'FrmDiverseConsultation', $data);
        $frmDiverseConsultation->setClose($btnClose);


        if ( $theme->page->generateMethod != 'generateAJAX' )
        {
            $theme->clearContent();
            $theme->AppendContent($frmDiverseConsultation);
        }
    }

}
?>