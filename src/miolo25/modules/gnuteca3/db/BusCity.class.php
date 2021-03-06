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
 * @author Jonas C. Rosa [jonas_rosa@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers \n
 * Eduardo Bonfandini   [eduardo@solis.coop.br]
 * Jamiel Spezia        [jamiel@solis.coop.br]
 *
 * @since
 * Class created on 11/07/2012
 *
 * */
$MIOLO = MIOLO::getInstance();
$MIOLO->getBusiness('gnuteca3', 'BusAuthenticate');

class BusinessGnuteca3BusCity extends GBusiness
{
    public $cityIdS;
    public $nameS;
    public $zipCodeS;
    public $stateIdS;
    public $countryIdS;
    public $ibgeIdS;
    
    public $cityId;
    public $name;
    public $_name;
    public $zipCode;
    public $stateId;
    public $countryId;
    public $ibgeId;

    function __construct()
    {
        //define a tabela e os campos padrão do bus
        parent::__construct('basCity', 'cityId', 'name,
                  zipCode,
                  stateId,
                  countryId,
                  ibgeId'
        );
    }

    public function listCity($object = FALSE)
    {
        return $this->autoList();
    }

    public function getCity($id)
    {
        //here you can pass how many where you want
        $get = $this->autoGet($id);
        $this->_name = $this->name;
        return $get;
    }

    public function searchCity($toObject = false)
    {
        $filters = array(
            'cityId' => 'equal',
            'name' => 'ilike',
            'zipCode' => 'ilike',
            'stateId' => 'ilike',
            'countryId' => 'ilike',
            'ibgeId' => 'ilike'
        );

        $this->clear();

        return $this->autoSearch($filters, $toObject);
    }

    public function insertCity()
    {
        $this->name = $this->_name;
        return $this->autoInsert();
    }

    public function updateCity()
    {
        $this->name = $this->_name;
        return $this->autoUpdate();
    }

    public function deleteCity($cityId)
    {
        return $this->autoDelete($cityId);
    }
}

?>