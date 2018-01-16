open TodoApp;

let str = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item, ~appReduce, _children) => {
  ...component,
  render: _self =>
    <div onClick=(appReduce(_event => ToggleItem(item.id)))>
      <input
        _type="checkbox"
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      (str(item.title))
    </div>
};