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
 * This class Fields Struct
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
 
class fieldsStruct extends fields
{
   /*
    * Function to construct that object, by default calls the parent function to set default 
    * values to some variables
    * @param: $sabStruct (sabStruct object)
    * @return: Nothing. 
    */
    public function __construct(sabStruct $sabStruct)
    {
        parent::__construct($sabStruct);
    }

    //Defines the calculation of modules of each field.
    public function generateModulesCalcField()
    {
        //Defines the module for calculating the digit verifier
        $this->digitableNumber->setModuleCalcField(1, 10);
        $this->digitableNumber->setModuleCalcField(2, 10);
        $this->digitableNumber->setModuleCalcField(3, 10);
    }
    
   /*
    *
    * This function is an abstract declaration on parent class, needed to generate the barcode
    * If you wish, the parent class has a method called "barCodeFixedValues" that implements rules of
    * barcode fixed values based on FEBRABAN defaults. See more at parent function on "include" path
    * ATTENTION: This function needs return a string containing length 25 and only numbers to process 
    *            the information correctly
    * @params: As you wish, by default, the sabStruct object
    * @return: (String) String with length 25
    */
    public function generateBarCode(sabStruct $sabStruct)
    {
        $this->barCodeDataFixedValuesWithFactor($sabStruct);
        $this->barCodeData->setBarCodeField('transferorCode', $sabStruct->getTransferorCode(), 11, 0);
        $this->barCodeData->setBarCodeField('invoiceNumber' , $sabStruct->getInvoiceOurNumber()              ,  7, 0);
        $this->barCodeData->setBarCodeField('constant'      , '00033'                                              ,  5, 0);
        $dv1 = $this->modulo10(substr(self::onlyNumbers($this->barCodeData->returnBarCode()),18,23));
        $this->barCodeData->setBarCodeField('dvS' , $sabStruct->getDV1DV2(substr(self::onlyNumbers($this->barCodeData->returnBarCode()),18,23),$dv1) ,  2, 0);
        $this->barCodeData->setBarCodeField('barCodeDV'     , $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())), 1, 0);
    }
}
?>
