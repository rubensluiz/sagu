<?php

/**
 * <--- Copyright 2011-2011 de Facimed - Faculdade de Ci�ncias Biom�tricas de Cacoal.
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
 * Finance income forecast generation handler.
 * Contains the menus to access income forecast generation process
 *
 * @author Leovan Tavares da Silva [leovan@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Equipe SAGU [sagu2@solis.coop.br]
 *
 * @since
 * Class created on 24/03/2011
 *
 **/

if (MIOLO::_REQUEST('event') == 'downloadVoucher_click')
{
    $voucher = MIOLO::_request('voucher');
    $voucher = unserialize(base64_decode($voucher));
    SAGU::returnAsFile('comprovante.txt', $voucher, 'application/txt');
}
else
{
    $module = MIOLO::getCurrentModule();
    $action = 'main:process:payProtocolFee';
    $title = _M('Receber taxa', $module);
    $managementForm = 'FrmPayProtocolFee';
    $searchForm = 'FrmPayProtocolFee';

    SAGU::handle($module, $action, $title, $searchForm, $managementForm, array('checkAccess' => FALSE));
}

?>
