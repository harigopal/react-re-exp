let str = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item: TodoApp.item, ~appReduce, _children) => {
  ...component,
  render: _self =>
    <div onClick=(appReduce(_event => TodoApp.ToggleItem(item.id)))>
      <input
        _type="checkbox"
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      (str(item.title))
    </div>
};