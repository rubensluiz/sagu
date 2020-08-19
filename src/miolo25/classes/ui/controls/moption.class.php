<?php
class MOption extends MInputControl
{
    public $checked;
    public $showValues;
    public $type = 'circle';
    public $control; // owner control of this Option


    public function __construct( $name = '', $value = null, $label = '', $checked = false, $id = false )
    {
        parent::__construct( $name, $value, $label );

        $this->checked = $checked;
    }


    public function setChecked( $checked )
    {
        if ( ! is_bool( $checked ) )
        {
            throw new Exception( _M('MOption::setChecked expects an boolean as parameter!') );
        }

        $this->checked = $checked;
    }


    public function setControl( $control )
    {
        $this->control = $control;
    }


    public function generate()
    {
        if ( is_array( $this->control->value ) )
        {
            $found = array_search( $this->value, $this->control->value );
            $checked = ( ! is_null($found) ) && ( $found !== false );
        }
        else
        {
            $checked = ( $this->value === $this->control->value );
        }

        $this->checked    = $this->checked || $checked;
        $this->showValues = $this->control->showValues;

        return $this->getRender( 'option' );
    }
}
?>