import deviceReducer from "./devices";
import notificationReducer from "./notification";
import signReducer from "./sign";


const reducers = {
    devices: deviceReducer,
    notification: notificationReducer,
    sign: signReducer
};

export default reducers;
