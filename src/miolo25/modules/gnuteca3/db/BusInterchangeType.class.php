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
 * InterchangeType business
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
 * Sandro Roberto Weisheimer [sandrow@solis.coop.br]
 *
 * @since
 * Class created on 20/02/2009
 *
 **/
class BusinessGnuteca3BusInterchangeType extends GBusiness
{
    public $interchangeTypeId;
    public $description;

    public $interchangeTypeIdS;
    public $descriptionS;


    public function __construct()
    {
    	$table = 'gtcInterchangeType';
    	$pkeys = 'interchangeTypeId';
    	$cols  = 'description';
        parent::__construct($table, $pkeys, $cols);
    }


    public function insertInterchangeType()
    {
        return $this->autoInsert();
    }


    public function updateInterchangeType()
    {
        return $this->autoUpdate();
    }


    public function getInterchangeType($interchangeTypeId)
    {
        $this->clear();
        return $this->autoGet($interchangeTypeId);
    }


    public function deleteInterchangeType($interchangeTypeId)
    {
        return $this->autoDelete($interchangeTypeId);
    }


    public function searchInterchangeType($toObject = FALSE)
    {
        $filters = array(
            'interchangeTypeId' => 'equals',
            'description'    => 'ilike'
        );
        $this->clear();
        return $this->autoSearch($filters, $toObject);
    }


    public function listInterchangeType()
    {
        return $this->autoList();
    }
}
?>
