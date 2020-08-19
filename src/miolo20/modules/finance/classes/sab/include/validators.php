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
 * Class Validators
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
 
class validators
{
    private $roundValue = 2;
    private $separator = '.';
    private $thousandSeparator = '';

   /*
    * TODO: Can choose date format as you wish. ;)
    * This function checks a date (only in dd/mm/yyyy format) at now
    * @params: $date (string) String containing the date to check
    * @return: (boolean) True if correct, otherwise false
    */
    public function checkDate($date)
    {
        if (is_string($date))
        {
            $d = explode('/', $date);
            if (sizeof($d) == 3)
            {
                if (checkDate($d[1], $d[0], $d[2]))
                {
                    return true;
                }
                else
                {
                    $this->error = _('Data inv�lida');
                    return false; 
                }
            }
            else
            {
                $this->error = _('Formato do texto inv�lido');
                return false;
            }
        }   
        $this->error = _('Tipo de data inv�lida');
        return false;
    }

   /*
    * This function checks a date (only in dd/mm/yyyy format)
    * @params: $date (string) String containing the date to check
    * @return: (boolean) True if correct, otherwise false
    */
    public function checkReal($value)
    {
        if (is_double($value) || is_int($value))
        {
            return number_format($value, $this->roundValue, $this->separator, $this->thousandSeparator);
        }
        else
        {
            $this->error = _('O valor informado n�o � do tipo real');
            return false;
        }
    }

   /*
    * This function checks a date (only in dd/mm/yyyy format)
    * @params: $date (string) String containing the date to check
    * @return: (boolean) True if correct, otherwise false
    */
    public function checkInt($value)
    {
        if (is_int($value))
        {
            return true; 
        }
        else
        {
            $this->error = _('O valor informado n�o � do tipo inteiro');
            return false;
        }
    }

   /*
    * This function checks a string
    * @params: $date (string) String containing the string to check :p
    * @return: (boolean) True if correct, otherwise false
    */
    public function checkString($value)
    {
        if (is_string($value))
        {
            return true; 
        }
        else
        {
            $this->error = _('O valor informado n�o � do tipo string');
            return false;
        }
    }

   /*
    * Return the errors if a validation failed
    * @params: No parameters required
    * @return: (String) The message containing details for the last error;
    *
    */
    public function getErrors()
    {
        return $this->error;
    }
}
?>
