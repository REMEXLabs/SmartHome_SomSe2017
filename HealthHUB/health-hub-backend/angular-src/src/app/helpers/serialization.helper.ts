export class SerializationHelper {
    static toInstance<Class>(obj: Class, json: any) : Class {

      for (var propName in json) {
          obj[propName] = json[propName]
      }

      return obj;
    }
}
