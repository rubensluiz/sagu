<?php
/**
 * <--- Copyright 2005-2011 de Solis - Cooperativa de Soluções Livres Ltda. e
 * Univates - Centro Universitário.
 * 
 * Este arquivo é parte do programa Gnuteca.
 * 
 * O Gnuteca é um software livre; você pode redistribuí-lo e/ou modificá-lo
 * dentro dos termos da Licença Pública Geral GNU como publicada pela Fundação
 * do Software Livre (FSF); na versão 2 da Licença.
 * 
 * Este programa é distribuído na esperança que possa ser útil, mas SEM
 * NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO
 * ou APLICAÇÃO EM PARTICULAR. Veja a Licença Pública Geral GNU/GPL em
 * português para maiores detalhes.
 * 
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU, sob o título
 * "LICENCA.txt", junto com este programa, se não, acesse o Portal do Software
 * Público Brasileiro no endereço www.softwarepublico.gov.br ou escreva para a
 * Fundação do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 * 
 *
 * Bond search form
 *
 * @author Moises Heberle [moises@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers \n
 * Eduardo Bonfandini [eduardo@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Luiz Gregory Filho [luiz@solis.coop.br]
 * Moises Heberle [moises@solis.coop.br]
 *
 * @since
 * Class created on 06/08/2008
 *
 **/

class FrmBondSearch extends GForm
{
    public function __construct()
    {
        $this->setAllFunctions('Bond',array('GrdBond', 'personIdS'), array('personId','linkId','oldDateValidate') );
        parent::__construct();
    }

    public function mainFields()
    {
        $fields[] = $personId = new GPersonLookup('personIdS', _M('Pessoa', $this->modules), 'person');

        $fields[] = new GSelection('linkIdS', '', _M('Código do grupo de usuário', $this->module), $this->business->listBond(true));

        $dateValidate = new MLabel(_M('Data de validade', $this->module) . ':');
        $dateValidate->setWidth(FIELD_LABEL_SIZE);
        $beginDateValidateS     = new MCalendarField('beginDateValidateS', $this->beginDateValidateS->value, null, FIELD_DATE_SIZE);
        $endDateValidateS       = new MCalendarField('endDateValidateS', $this->endDateValidateS->value, null, FIELD_DATE_SIZE);
        $fields[] = new GSelection('activeLink', '', _M('Ativos', $this->module), GUtil::listYesNo(0));
        $fields[] = new GContainer('hctDates', array($dateValidate, $beginDateValidateS, $endDateValidateS));
        $validators[] = new MDateDMYValidator('beginDateValidateS');

        $this->setFields($fields);
        $this->setValidators($validators);
    }
}
?>
