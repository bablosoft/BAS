<span id="action-add">
  <div class="container-fluid">
  	<div class="col-xs-12">
          <form class="form-horizontal">
            <div class="form-group">
              <div class="col-xs-2">
                <div class="input-group">
                  <span data-preserve="true" data-preserve-type="select" data-preserve-id="Table">
                    <select class="form-control input-sm" id="Table" placeholder="Result">
                    	  <% _Schema.forEach(function(t){ %>
  							         <option value="<%= t.id %>"><%= t.description %></option>
                    	  <% }) %>
                    </select>
                  </span>
                </div>
              </div>
              <label class="control-label text-right tr" style="padding-top:5px !important;">Table</label>
            </div>
          </form>
        </div>
      
      <div class="container-fluid" id="database-filters" style="margin-top:10px">
        <div class="col-xs-12">
          <button type="button" class="btn btn-default btn-sm" id="database-filters-add"><i class="fa fa-filter" aria-hidden="true"></i> <span class="tr">Add filter</span></button>
          <button type="button" class="btn btn-default btn-sm" id="database-filters-clear"><i class="fa fa-eraser" aria-hidden="true"></i> <span class="tr">Remove all filters</span></button>
          
        </div>
      </div>
      <div class="container-fluid" id="database-filters" >
        <div class="col-xs-12">
      
          <div id="database-filters-data">
          </div>
        </div>
      </div>
  </div>

  <div style="margin-top:10px">
  </div>

  <%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
</span>
<span id="filter-add" style="display:none">

<div class="container-fluid">
  <div class="col-xs-12">

    <span class="tr">Field</span>:
    <select class="form-control input-sm" id="FilterFieldInput">
    </select>
    <span class="tr">Filter type</span>:
    <select class="form-control input-sm" id="FilterTypeInput">
    </select>
  </div>
</div>
<div style="margin-top:10px" id="FiledValueInput">
    <%= _.template($('#input_constructor').html())({id:"Value", description:tr("Value"), default_selector: "string"}) %>
</div>

<div class="container-fluid" style="margin-top:0px">
  <div class="col-xs-12">

    <button type="button" class="btn btn-primary filterok standartbutton tr" style="margin-top:5px" >Ok</button>
    <button type="button" class="btn btn-default filtercancel standartbutton tr" style="margin-top:5px" >Cancel</button>
  </div>
</div>

</span>
