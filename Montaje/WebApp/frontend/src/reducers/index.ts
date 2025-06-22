import deviceReducer from "./devices";
import notificationReducer from "./notification";
import signReducer from "./sign";


const reducers = {
    devices: deviceReducer,
    sign: signReducer,
    notification: notificationReducer
}

export default reducers;