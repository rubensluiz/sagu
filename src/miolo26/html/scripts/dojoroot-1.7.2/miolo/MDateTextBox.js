dojo.provide("MDateTextBox");

dojo.require("dijit.form.DateTextBox");

dojo.declare("MDateTextBox", [dijit.form.DateTextBox], {
    maxLength: 10,
    serialize: function(d, options) {
        // dijit.form.DateTextBox has a standard date format (ansi) : yyyy-mm-dd
        // so, build a new Dijit Widget to force date format to 'dd/mm/yyyy' on submit
        return dojo.date.locale.format(d, {
            selector:'date', 
            datePattern:'dd/MM/yyyy'
        }).toLowerCase();
    },
    _onKey: function (e) {
        this.inherited(arguments);

        var value = this.attr('displayedValue');
        if ((value.length==2 || value.length==5 ) && e.charOrCode != dojo.keys.BACKSPACE && e.charOrCode != '/')
        {
            this.attr('displayedValue', this.attr('displayedValue') + '/');
        }
    },
    // Overrides the openDropDown to do not focus the calendar widget when opened
    openDropDown: function (/*Function*/ callback) {
        this.inherited(arguments);

        this.dropDown.autoFocus = false;
        this.dropDown.handleKey = function (/*Event*/ evt) {
            if ( evt.charOrCode == dojo.keys.ENTER ) {
                this.destroy();
            }

            return true;
        };
    },
    // overrides the onChange function to call the event of the MCalendarField component
    onChange: function () {
        // changes the value in the valueNode to get the new one in the POST
        this.valueNode.value = this.attr('displayedValue');

        // invokes parent onChange
        dijit.form.DateTextBox.superclass.onChange.apply(this,arguments);

        // tests if the whole date has been informed and then fires the change event
        if ( this.valueNode.value.length == this.maxLength )
        {
            if(dojo.doc.createEvent)
            {
                var evObj = dojo.doc.createEvent("HTMLEvents");
                evObj.initEvent( 'change' , true, true);
                dojo.byId( this.id ).dispatchEvent(evObj);
            }
            else if (dojo.doc.createEventObject) // IE
            {
                dojo.byId( this.id ).fireEvent( 'onchange' );
            }
        }
    },
    // set displayed value
    setJsValue: function (value) {
        this.attr('displayedValue', value);
    }
});
