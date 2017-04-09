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
    <%= _.template($('#input_constructor').html())({id:"Name", description:tr("Name"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#input_constructor').html())({id:"Description", description:tr("Description"), default_selector: "string", disable_int:true}) %>
    <%= _.template($('#variable_constructor').html())({id:"GroupId", description:tr("Group id"), default_variable: "NEW_GROUP_ID"}) %>
</div>
<%= _.template($('#back').html())({action:"executeandadd", visible:true}) %>
