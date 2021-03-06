<?php

/**
 * <--- Copyright 2005-2015 de Solis - Cooperativa de Solu��es Livres Ltda.
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
 * Residencia medica - Exibe unidades tematicas em que usuario � preceptor
 *
 * @author Joao Francisco Padilha Souza [joao@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * 
 *
 * @since
 * Class created on 06/02/2015
 */
$module = SAGU::getFileModule(__FILE__);

$mioloUserName = trim($MIOLO->getLogin()->id);
$busPerson = new BusinessBasicBusPerson();
$personData = $busPerson->getPersonByMioloUserName($mioloUserName);

if ( !$personData->isPreceptorUnidadeTematicaMedico )
{
    $MIOLO->error(_M('Voc� deve ser preceptor de alguma unidade tem�tica para acessar esta tela.', $module));
}

SAGU::handle('resmedica', 'main:unidadesTematicasDoPreceptor', _M('Resid�ncia m�dica', $module), 'FrmUnidadesTematicasDoPreceptor', 'FrmResidenciaMedica', array( 'checkAccess' => false ));
?>