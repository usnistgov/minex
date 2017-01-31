/*
 * MINEX III table.
 */
$(document).ready(function() {
	var minexiii_dt = $('#minexiii_results').DataTable({
		"paging":false,
		"columnDefs": [
			{
			"targets": [5,6,8,9,10],
			"visible": false,
			}
		],
		colReorder: {
			fixedColumnsLeft: 1
		},
		scrollY: "300px",
		scrollCollapse: true,
		buttons: ['colvis', 'csvHtml5'],

		// Dynamic responsive columns. Must also set table class to dt-responsive.
		dom: 'Bfrtip',
		scrollX: false,
		responsive: {
			details: {
				display: $.fn.dataTable.Responsive.display.modal( {
					header: function ( row ) {
						var data = row.data();
						return 'Details for '+data[0];
					}
				} ),
				renderer: $.fn.dataTable.Responsive.renderer.tableAll( {
					tableClass: 'ui table'
				} )
			}
		}

	}); /* DataTable */
}); /* document.ready */

/******************************************************************************/

/*
 * Ongoing MINEX table.
 */
$(document).ready(function() {
	var ominex_dt = $('#ominex_results').DataTable({
		"paging":false,
		"columnDefs": [
			{
			"targets": [4,6,7,8,9],
			"visible": false,
			}
		],
		colReorder: {
			fixedColumnsLeft: 1
		},
		scrollY: "300px",
		scrollCollapse: true,
		buttons: ['colvis', 'csvHtml5'],

		// Dynamic responsive columns. Must also set table class to dt-responsive.
		dom: 'Bfrtip',
		scrollX: false,
		responsive: {
			details: {
				display: $.fn.dataTable.Responsive.display.modal( {
					header: function ( row ) {
						var data = row.data();
						return 'Details for '+data[0];
						      }
				} ),
				renderer: $.fn.dataTable.Responsive.renderer.tableAll( {
					tableClass: 'ui table'
				} )
			}

		}
	}); /* DataTable */
}); /* document.ready */
