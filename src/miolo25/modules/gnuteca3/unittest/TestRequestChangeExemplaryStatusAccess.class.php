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
 *  Teste unitário
 *
 * @author Eduardo Bonfandini [eduardo@solis.coop.br]
 *
 * @version $id$
 *
 * \b Maintainers: \n
 * Eduardo Bonfandini [eduardo@solis.coop.br]
 * Jader Osvino Fiegenbaum [jader@solis.coop.br]
 *
 * @since
 * Creation date 25/10/2011
 *
 **/
include_once '../classes/GBusinessUnitTest.class.php';
class TestRequestChangeExemplaryStatusAccess extends GBusinessUnitTest
{
    public function setUp()
    {
        parent::setUp('RequestChangeExemplaryStatusAccess');
        
        $data = new stdClass();
        $data->basLinkId = $data->basLinkIdS = '1';
        $data->exemplaryStatusId = $data->exemplaryStatusIdS = '2';
        $data->description = $data->descriptionS = 'Estado inicial';
        $data->isModified = $data->isModifiedS = 't';
        $data->functionMode = $data->functionModeS = 'manage';
        $data->exemplaryStatus = $data->exemplaryStatusS = array (  0 =>   stdClass::__set_state(array(     'module' => 'gnuteca3',     'action' => 'main:configuration:requestChangeExemplaryStatusAccess',     '__mainForm__EVENTTARGETVALUE' => 'forceAddToTable',     'function' => 'insert',     'basLinkId' => '1',     'exemplaryStatusId' => '0',     'description' => 'Estado inicial',     'GRepetitiveField' => 'exemplaryStatus',     'arrayItemTemp' => NULL,     'keyCode' => '',     'isModified' => 't',     'functionMode' => 'manage',     'frm4ea6e2baab328_action' => 'http://gnutecatrunk.guilherme/index.php?module=gnuteca3&action=main:configuration:requestChangeExemplaryStatusAccess&__mainForm__EVENTTARGETVALUE=tbBtnNew:click&function=insert',     '__mainForm__VIEWSTATE' => '',     '__mainForm__ISPOSTBACK' => 'yes',     '__mainForm__EVENTARGUMENT' => '',     '__FORMSUBMIT' => '__mainForm',     '__ISAJAXCALL' => 'yes',     '__THEMELAYOUT' => 'dynamic',     '__MIOLOTOKENID' => '',     '__ISFILEUPLOAD' => 'no',     '__ISAJAXEVENT' => 'yes',     'cpaint_response_type' => 'json',     'insertData' => true,     'arrayItem' => 0,  )),);

        $this->business->setData($data);
    }
}
?>