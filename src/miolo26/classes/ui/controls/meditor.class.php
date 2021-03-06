<?php

/**
 * MEditor Class
 * WYSIWYG Component to generate HTML content
 *
 * @author Daniel Hartmann [daniel@solis.coop.br]
 *
 * @version $id$
 *
 * \b Maintainers: \n
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Daniel Hartmann [daniel@solis.coop.br]
 *
 * @since
 * Creation date 2011/02/18
 *
 * \b Organization: \n
 * SOLIS - Cooperativa de Soluções Livres \n
 *
 * \b CopyRight: \n
 * Copyright (c) 2011 SOLIS - Cooperativa de Soluções Livres \n
 *
 * \b License: \n
 * Licensed under GPLv2 (for further details read the COPYING file or http://www.gnu.org/licenses/gpl.html)
 *
 * \b History: \n
 * See history in CVS repository: http://www.miolo.org.br
 *
 */

$MIOLO = MIOLO::getInstance();
$MIOLO->page->addScript('m_editor.js');
$MIOLO->page->addScript('ckeditor/ckeditor.js');

class MEditor extends MMultiLineField
{
    const BUTTON_SOURCE = 'Source';
    const BUTTON_SAVE = 'Save';
    const BUTTON_NEW_PAGE = 'NewPage';
    const BUTTON_PREVIEW = 'Preview';
    const BUTTON_TEMPLATES = 'Templates';
    const BUTTON_CUT = 'Cut';
    const BUTTON_COPY = 'Copy';
    const BUTTON_PASTE = 'Paste';
    const BUTTON_PASTE_TEXT = 'PasteText';
    const BUTTON_PASTE_FROM_WORD = 'PasteFromWord';
    const BUTTON_PRINT = 'Print';
    const BUTTON_SPELL_CHECKER = 'SpellChecker';
    const BUTTON_SCAYT = 'Scayt';
    const BUTTON_UNDO = 'Undo';
    const BUTTON_REDO = 'Redo';
    const BUTTON_FIND = 'Find';
    const BUTTON_REPLACE = 'Replace';
    const BUTTON_SELECT_ALL = 'SelectAll';
    const BUTTON_REMOVE_FORMAT = 'RemoveFormat';
    const BUTTON_FORM = 'Form';
    const BUTTON_CHECKBOX = 'Checkbox';
    const BUTTON_RADIO = 'Radio';
    const BUTTON_TEXT_FIELD = 'TextField';
    const BUTTON_TEXT_AREA = 'Textarea';
    const BUTTON_SELECT = 'Select';
    const BUTTON_BUTTON = 'Button';
    const BUTTON_IMAGE_BUTTON = 'ImageButton';
    const BUTTON_HIDDEN_FIELD = 'HiddenField';
    const BUTTON_BIDI_LTR = 'BidiLtr';
    const BUTTON_BIDI_RTL = 'BidiRtl';
    const BUTTON_BOLD = 'Bold';
    const BUTTON_ITALIC = 'Italic';
    const BUTTON_UNDERLINE = 'Underline';
    const BUTTON_STRIKE = 'Strike';
    const BUTTON_SUBSCRIPT = 'Subscript';
    const BUTTON_SUPERSCRIPT = 'Superscript';
    const BUTTON_NUMBERED_LIST = 'NumberedList';
    const BUTTON_BULLETED_LIST = 'BulletedList';
    const BUTTON_OUTDENT = 'Outdent';
    const BUTTON_INDENT = 'Indent';
    const BUTTON_BLOCKQUOTE = 'Blockquote';
    const BUTTON_CREATE_DIV = 'CreateDiv';
    const BUTTON_JUSTIFY_LEFT = 'JustifyLeft';
    const BUTTON_JUSTIFY_CENTER = 'JustifyCenter';
    const BUTTON_JUSTIFY_RIGHT = 'JustifyRight';
    const BUTTON_JUSTIFY_BLOCK = 'JustifyBlock';
    const BUTTON_LINK = 'Link';
    const BUTTON_UNLINK = 'Unlink';
    const BUTTON_ANCHOR = 'Anchor';
    const BUTTON_IMAGE = 'Image';
    const BUTTON_FLASH = 'Flash';
    const BUTTON_TABLE = 'Table';
    const BUTTON_HORIZONTAL_RULE = 'HorizontalRule';
    const BUTTON_SMILEY = 'Smiley';
    const BUTTON_SPECIAL_CHAR = 'SpecialChar';
    const BUTTON_PAGE_BREAK = 'PageBreak';
    const BUTTON_STYLES = 'Styles';
    const BUTTON_FORMAT = 'Format';
    const BUTTON_FONT = 'Font';
    const BUTTON_FONT_SIZE = 'FontSize';
    const BUTTON_TEXT_COLOR = 'TextColor';
    const BUTTON_BG_COLOR = 'BGColor';
    const BUTTON_MAXIMIZE = 'Maximize';
    const BUTTON_SHOW_BLOCKS = 'ShowBlocks';
    const BUTTON_ABOUT = 'About';
    const BUTTON_SEPARATOR = '-';
    const BUTTON_LINE_SEPARATOR = '/';
    const BUTTON_CUSTOM_BUTTON = 'custombutton';

    private $config;

    /**
     * @var integer Store the last custom button index.
     */
    private $customButtonCounter = 0;

    /**
     * MEditor constructor
     *
     * @param string $name Element name
     * @param string $value HTML default content
     * @param string $label Label
     */
    public function __construct($name=NULL, $value='', $label='', $buttons=NULL)
    {
        parent::__construct($name, $value, $label);

        // set the form's onsubmit to update the element value
        $this->page->onload("meditor.connect('$name');");

        // enable custombutton plugin
        $this->config['extraPlugins'] = 'custombutton';

        if ( !$buttons )
        {
            $buttons[] = array(self::BUTTON_BOLD, self::BUTTON_ITALIC, self::BUTTON_UNDERLINE);
            $buttons[] = array(self::BUTTON_FONT, self::BUTTON_FONT_SIZE);
            $buttons[] = array(self::BUTTON_TEXT_COLOR, self::BUTTON_BG_COLOR);
            $buttons[] = array(self::BUTTON_LINK);
            $buttons[] = array(self::BUTTON_JUSTIFY_LEFT, self::BUTTON_JUSTIFY_CENTER, self::BUTTON_JUSTIFY_RIGHT, self::BUTTON_JUSTIFY_BLOCK);
            $buttons[] = array(self::BUTTON_NUMBERED_LIST, self::BUTTON_BULLETED_LIST, self::BUTTON_OUTDENT, self::BUTTON_INDENT);
            $buttons[] = array(self::BUTTON_CUT, self::BUTTON_COPY, self::BUTTON_PASTE);
            $buttons[] = array(self::BUTTON_UNDO, self::BUTTON_REDO);
        }
        $this->setButtons($buttons);

        $this->setLanguage($this->manager->getConf('i18n.language'));
        $this->setClass('mEditor');
    }

    /**
     * Create a custom button on toolbar
     *
     * @param string $label Button label.
     * @param string $command Javascript code. It can use the parameter editor
     *                         to maniulate the CKEDITOR instance.
     * @param string $icon Image URL (16x16).
     */
    public function addCustomButton($label, $command, $icon)
    {
        $i = $this->customButtonCounter++;
        $button = '{';
        $button .= "label: '$label',";
        $button .= "command: function(editor) { $command },";
        $button .= "icon: '$icon'";
        $button .= '}';

        $this->page->addJsCode("meditor.custombutton[$i] = $button;");
        $this->config['toolbar'][] = array(self::BUTTON_CUSTOM_BUTTON . $i);
    }

    /**
     * Set the component toolbar buttons.
     * You must inform a matrix with the BUTTON_* constants.
     *
     * @param array $buttons
     */
    public function setButtons($buttons)
    {
        if ( !is_array($buttons) )
        {
            $buttons = array(array($buttons));
        }
        elseif ( !is_array($buttons[0]) )
        {
            $buttons = array($buttons);
        }

        $this->config['toolbar'] = $buttons;
    }

    /**
     * @param string $lang Set the language
     */
    public function setLanguage($lang)
    {
        $this->config['language'] = $lang;
    }

    /**
     * @param string $color Set the UI color in hexadecimal
     */
    public function setColor($color)
    {
        $this->config['uiColor'] = $color;
    }

    /**
     * Set a value to a configuration parameter.
     * You can check the possible configurations here:
     * http://docs.cksource.com/CKEditor_3.x/Developers_Guide
     *
     * @param string $key Configuration parameter
     * @param string $value Configuration value
     */
    public function setConfigValue($key, $value)
    {
        $this->config[$key] = $value;
    }

    /**
     * @param string $key Configuration parameter
     * @return string Configuration value
     */
    public function getConfigValue($key)
    {
        return $this->config[$key];
    }

    /**
     * @return array Return the whole configuration array
     */
    public function getConfig()
    {
        return $this->config;
    }

    /**
     * @param array $config Set the whole configuration array
     */
    public function setConfig($config)
    {
        $this->config = $config;
    }

    /**
     * Disable tag visualization on the bottom bar.
     * It adds elementsPath to removePlugins configuration.
     */
    public function disableElementsPath()
    {
        $removePlugins = array();

        if ( $this->config['removePlugins'] )
        {
            $removePlugins = explode(',', $this->config['removePlugins']);
        }

        $removePlugins[] = 'elementspath';
        $this->config['removePlugins'] = implode(',', array_unique($removePlugins));
    }

    /**
     * Enable tag visualization on the bottom bar.
     */
    public function enableElementsPath()
    {
        if ( $this->config['removePlugins'] )
        {
            $removePlugins = explode(',', $this->config['removePlugins']);
            foreach ( $removePlugins as $key => $plugin )
            {
                if ( $plugin == 'elementspath' )
                {
                    unset($removePlugins[$key]);
                }
            }
            $this->config['removePlugins'] = implode(',', $removePlugins);
        }
    }

    /**
     * Parse the configuration array to json format and call the parent's generate method
     *
     * @return string HTML generated component (textarea)
     */
    public function generate()
    {
        $jsonConfig = json_encode($this->config);

        $this->page->onload("if ( CKEDITOR.instances.$this->name ) { CKEDITOR.remove(CKEDITOR.instances.$this->name); } CKEDITOR.replace('$this->name', $jsonConfig);");

        return parent::generate();
    }
}
?>
