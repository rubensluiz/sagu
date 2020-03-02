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
 * Finance message handler.
 * Contains the menus to access country registers
 *
 * @author Bruno E. Fuhr [bruno@solis.com.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Bruno E. Fuhr [bruno@solis.com.br]
 *
 * @since
 * Class created on 21/01/2014
 *
 **/

$module = MIOLO::getCurrentModule();
$title = _M('Formas de pagamento', $module);
$managementForm = 'FrmFormasDePagamento';
$searchForm = 'FrmFormasDePagamento';

SAGU::handle($module, $action, $title, $searchForm, $managementForm);

?>